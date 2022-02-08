#include "amici/backwardproblem.h"

#include "amici/model.h"
#include "amici/solver.h"
#include "amici/exception.h"
#include "amici/edata.h"
#include "amici/forwardproblem.h"
#include "amici/steadystateproblem.h"
#include "amici/misc.h"

#include <cstring>
#include <cassert>

namespace amici {

BackwardProblem::BackwardProblem(const ForwardProblem &fwd,
                                 const SteadystateProblem *posteq):
    model_(fwd.model),
    solver_(fwd.solver),
    edata_(fwd.edata),
    t_(fwd.getTime()),
    xB_(fwd.model->nx_solver),
    dxB_(fwd.model->nx_solver),
    xQB_(fwd.model->nJ*fwd.model->nplist()),
    x_disc_(fwd.getStatesAtDiscontinuities()),
    x_old_disc_(fwd.getStatesBeforeDiscontinuities()),
    xdot_disc_(fwd.getRHSAtDiscontinuities()),
    xdot_old_disc_(fwd.getRHSBeforeDiscontinuities()),
    sx0_(fwd.getStateSensitivity()),
    nroots_(fwd.getNumberOfRoots()),
    discs_(fwd.getDiscontinuities()),
    root_idx_(fwd.getRootIndexes()),
    dJydx_(fwd.getDJydx()),
    dJzdx_(fwd.getDJzdx()) {
        /* complement dJydx from postequilibration. This shouldn't overwrite
         * anything but only fill in previously 0 values, as only non-inf
         * timepoints are filled from fwd.
         */
        for (int it = 0; it < fwd.model->nt(); it++) {
            if (std::isinf(fwd.model->getTimepoint(it))) {
                if (!posteq)
                    throw AmiException("Model has non-finite timepoint but, "
                                       "postequilibration did not run");

                /* copy adjoint update to postequilibration */
                writeSlice(slice(posteq->getDJydx(), it,
                                 fwd.model->nx_solver * fwd.model->nJ),
                           slice(dJydx_, it,
                                 fwd.model->nx_solver * fwd.model->nJ));

                /* If adjoint sensis were computed, copy also quadratures */
                xQB_.zero();
                xQB_ = posteq->getEquilibrationQuadratures();
            }
        }

    }


void BackwardProblem::workBackwardProblem() {

    if (model_->nx_solver <= 0 ||
        solver_->getSensitivityOrder() < SensitivityOrder::first ||
        solver_->getSensitivityMethod() != SensitivityMethod::adjoint ||
        model_->nplist() == 0) {
        return;
    }

    int it = model_->nt() - 1;
    /* If we have posteq, infinity timepoints were already treated */
    for (int jt = model_->nt() - 1; jt >= 0; jt--)
        if (std::isinf(model_->getTimepoint(jt)))
            --it;

    /* initialize state vectors, depending on postequilibration */
    model_->initializeB(xB_, dxB_, xQB_, it < model_->nt() - 1);

    if ((it >= 0 || !discs_.empty()) && model_->getTimepoint(it) > model_->t0())
    {
        handleDataPointB(it);
        solver_->setupB(&which, model_->getTimepoint(it), model_, xB_, dxB_, xQB_);
        --it;

        while (it >= 0 || discs_.size() > 0) {
            /* check if next timepoint is a discontinuity or a data-point */
            double tnext = getTnext(it);

            if (tnext < t_) {
                solver_->runB(tnext);
                solver_->writeSolutionB(&t_, xB_, dxB_, xQB_, which);
            }

            /* handle data-point */
            if (it >=0 && tnext == model_->getTimepoint(it)) {
                handleDataPointB(it);
                it--;
            }

            /* handle discontinuity */
            if (!discs_.empty() && tnext == discs_.back()) {
                discs_.pop_back();
                handleEventB();
            }

            /* reinit states */
            solver_->reInitB(which, t_, xB_, dxB_);
            solver_->quadReInitB(which, xQB_);
        }
    }

    /* we still need to integrate from first datapoint to tstart */
    if (t_ > model_->t0()) {
        /* solve for backward problems */
        solver_->runB(model_->t0());
        solver_->writeSolutionB(&t_, xB_, dxB_, xQB_, which);
    }

    if (edata_ && edata_->t_presim > 0) {
        ConditionContext cc(model_, edata_, FixedParameterContext::presimulation);
        solver_->runB(model_->t0() - edata_->t_presim);
        solver_->writeSolutionB(&t_, xB_, dxB_, xQB_, which);
    }
}


void BackwardProblem::handleEventB() {
    auto rootidx = root_idx_.back();
    this->root_idx_.pop_back();

    auto x_disc = this->x_disc_.back();
    this->x_disc_.pop_back();

    auto x_old_disc = this->x_old_disc_.back();
    this->x_old_disc_.pop_back();

    auto xdot_disc = this->xdot_disc_.back();
    this->xdot_disc_.pop_back();

    auto xdot_old_disc = this->xdot_old_disc_.back();
    this->xdot_old_disc_.pop_back();

    auto x_in_event = AmiVector(x_disc);
    for (int iv = 0; iv < x_in_event.getLength(); iv++)
        x_in_event[iv] = 0.5 * (x_disc.at(iv) + x_old_disc.at(iv));

    auto xdot_in_event = AmiVector(xdot_disc);
    for (int iv = 0; iv < xdot_in_event.getLength(); iv++)
        xdot_in_event[iv] = 0.5 * (xdot_disc.at(iv) + xdot_old_disc.at(iv));

    model_->updateHeavisideB(rootidx.data());

    auto delta_x = AmiVector(x_disc.getLength());
    for (int iv = 0; iv < xdot_in_event.getLength(); iv++)
        delta_x[iv] = (x_disc.at(iv) - x_old_disc.at(iv));

    for (int ie = 0; ie < model_->ne; ie++) {

        if (rootidx[ie] == 1) {

            model_->addAdjointQuadratureEventUpdate(xQB_, ie, t_, x_old_disc, xB_,
                                                    xdot_disc, xdot_old_disc,
                                                    delta_x);
            model_->addAdjointStateEventUpdate(xB_, ie, t_, x_old_disc,
                                               xdot_disc, xdot_old_disc,
                                               delta_x);

            if (model_->nz > 0) {
                for (int ix = 0; ix < model_->nxtrue_solver; ++ix) {
                    for (int iJ = 0; iJ < model_->nJ; ++iJ) {
                        xB_[ix + iJ * model_->nxtrue_solver] +=
                            dJzdx_[iJ + ( ix + nroots_[ie] * model_->nx_solver )
                                           * model_->nJ];
                    }
                }
            }
            nroots_[ie]--;
        }
    }
}

void BackwardProblem::handleDataPointB(const int it) {
    solver_->storeDiagnosisB(which);

    for (int ix = 0; ix < model_->nxtrue_solver; ix++) {
        for (int iJ = 0; iJ < model_->nJ; iJ++)
            // we only need the 1:nxtrue_solver (not the nx_true) slice here!
            xB_[ix + iJ * model_->nxtrue_solver] +=
                dJydx_[iJ + ( ix + it * model_->nx_solver ) * model_->nJ];
    }
}

realtype BackwardProblem::getTnext(const int it) {
    if (it < 0 && discs_.empty()) {
        throw AmiException(
            "No more timepoints (it=%d, ie=%d) available at %f. This should "
            "not happen, please report a bug including this stacktrace at "
            "https://github.com/AMICI-dev/AMICI/issues/new/choose",
            it, discs_.size(), this->t_
        );
    }

    if (!discs_.empty() &&
        (it < 0 || discs_.back() > model_->getTimepoint(it))) {
        double tdisc = discs_.back();
        return tdisc;
    }

    return model_->getTimepoint(it);
}

} // namespace amici
