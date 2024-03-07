#ifndef _amici_model_events_h
#define _amici_model_events_h
/* Generated by amiwrap (R2017b) 8b324bca5b796a93094195d22a023e5f8e945ef1 */
#include <cmath>
#include <memory>
#include "amici/defines.h"
#include <sunmatrix/sunmatrix_sparse.h> //SUNMatrixContent_Sparse definition
#include "amici/solver_cvodes.h"
#include "amici/model_ode.h"

namespace amici {

class Solver;

namespace model_model_events{

extern void JSparse_model_events(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void Jrz_model_events(double *nllh, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz);
extern void Jy_model_events(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void Jz_model_events(double *nllh, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz);
extern void dJrzdsigma_model_events(double *dJrzdsigma, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz);
extern void dJrzdz_model_events(double *dJrzdz, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz);
extern void dJydsigma_model_events(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dJydy_model_events(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dJzdsigma_model_events(double *dJzdsigma, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz);
extern void dJzdz_model_events(double *dJzdz, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz);
extern void deltasx_model_events(double *deltasx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *sx, const realtype *stau, const realtype *tcl);
extern void drzdx_model_events(double *drzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h);
extern void dxdotdp_model_events(realtype *dxdotdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp);
extern void dydp_model_events(double *dydp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp);
extern void dydx_model_events(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void dzdx_model_events(double *dzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h);
extern void root_model_events(realtype *root, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl);
extern void rz_model_events(double *rz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h);
extern void sigmay_model_events(double *sigmay, const realtype t, const realtype *p, const realtype *k, const realtype *y);
extern void sigmaz_model_events(double *sigmaz, const realtype t, const realtype *p, const realtype *k);
extern void srz_model_events(double *srz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip);
extern void stau_model_events(double *stau, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl, const realtype *sx, const int ip, const int ie);
extern void sz_model_events(double *sz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip);
extern void x0_model_events(realtype *x0, const realtype t, const realtype *p, const realtype *k);
extern void xdot_model_events(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w);
extern void y_model_events(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w);
extern void z_model_events(double *z, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h);

class Model_model_events : public amici::Model_ODE {
public:
    Model_model_events()
        : amici::Model_ODE(
              amici::ModelDimensions(
                  3,
                  3,
                  3,
                  3,
                  0,
                  4,
                  4,
                  1,
                  1,
                  2,
                  2,
                  6,
                  6,
                  0,
                  1,
                  0,
                  0,
                  0,
                  0,
                  0,
                  {},
                  0,
                  0,
                  0,
                  4,
                  0,
                  1
              ),
              amici::SimulationParameters(
                  std::vector<realtype>(4, 1.0),
                  std::vector<realtype>(4, 1.0)
              ),
              amici::SecondOrderMode::none,
              std::vector<realtype>{0, 0, 0},
              std::vector<int>{1, 2})
              {};

    amici::Model* clone() const override { return new Model_model_events(*this); };

    std::string getAmiciCommit() const override { return "8b324bca5b796a93094195d22a023e5f8e945ef1"; };

    void fJSparse(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        JSparse_model_events(JSparse, t, x, p, k, h, w, dwdx);
    }

    void fJrz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
        Jrz_model_events(nllh, iz, p, k, rz, sigmaz);
    }

    void fJy(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        Jy_model_events(nllh, iy, p, k, y, sigmay, my);
    }

    void fJz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
        Jz_model_events(nllh, iz, p, k, z, sigmaz, mz);
    }

    void fdJrzdsigma(double *dJrzdsigma, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
        dJrzdsigma_model_events(dJrzdsigma, iz, p, k, rz, sigmaz);
    }

    void fdJrzdz(double *dJrzdz, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
        dJrzdz_model_events(dJrzdz, iz, p, k, rz, sigmaz);
    }

    void fdJydsigma(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydsigma_model_events(dJydsigma, iy, p, k, y, sigmay, my);
    }

    void fdJydy(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydy_model_events(dJydy, iy, p, k, y, sigmay, my);
    }

    void fdJzdsigma(double *dJzdsigma, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
        dJzdsigma_model_events(dJzdsigma, iz, p, k, z, sigmaz, mz);
    }

    void fdJzdz(double *dJzdz, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
        dJzdz_model_events(dJzdz, iz, p, k, z, sigmaz, mz);
    }

    void fdeltaqB(double *deltaqB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB) override {
    }

    void fdeltasx(double *deltasx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *sx, const realtype *stau, const realtype *tcl) override {
        deltasx_model_events(deltasx, t, x, p, k, h, w, ip, ie, xdot, xdot_old, sx, stau, tcl);
    }

    void fdeltax(double *deltax, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old) override {
    }

    void fdeltaxB(double *deltaxB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB) override {
    }

    void fdrzdp(double *drzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    void fdrzdx(double *drzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
        drzdx_model_events(drzdx, ie, t, x, p, k, h);
    }

    void fdsigmaydp(double *dsigmaydp, const realtype t, const realtype *p, const realtype *k, const realtype *y, const int ip) override {
    }

    void fdsigmazdp(double *dsigmazdp, const realtype t, const realtype *p, const realtype *k, const int ip) override {
    }

    void fdwdp(realtype *dwdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl, const realtype *stcl, const realtype *spl, const realtype *sspl, bool include_static) override {
    }

    void fdwdx(realtype *dwdx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl, const realtype *spl, bool include_static) override {
    }

    void fdxdotdp(realtype *dxdotdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp) override {
        dxdotdp_model_events(dxdotdp, t, x, p, k, h, ip, w, dwdp);
    }

    void fdydp(double *dydp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp) override {
        dydp_model_events(dydp, t, x, p, k, h, ip, w, dwdp);
    }

    void fdydx(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        dydx_model_events(dydx, t, x, p, k, h, w, dwdx);
    }

    void fdzdp(double *dzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    void fdzdx(double *dzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
        dzdx_model_events(dzdx, ie, t, x, p, k, h);
    }

    void froot(realtype *root, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl) override {
        root_model_events(root, t, x, p, k, h, tcl);
    }

    void frz(double *rz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
        rz_model_events(rz, ie, t, x, p, k, h);
    }

    void fsigmay(double *sigmay, const realtype t, const realtype *p, const realtype *k, const realtype *y) override {
        sigmay_model_events(sigmay, t, p, k, y);
    }

    void fsigmaz(double *sigmaz, const realtype t, const realtype *p, const realtype *k) override {
        sigmaz_model_events(sigmaz, t, p, k);
    }

    void fsrz(double *srz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
        srz_model_events(srz, ie, t, x, p, k, h, sx, ip);
    }

    void fstau(double *stau, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl, const realtype *sx, const int ip, const int ie) override {
        stau_model_events(stau, t, x, p, k, h, tcl, sx, ip, ie);
    }

    void fsx0(realtype *sx0, const realtype t,const realtype *x0, const realtype *p, const realtype *k, const int ip) override {
    }

    void fsz(double *sz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
        sz_model_events(sz, ie, t, x, p, k, h, sx, ip);
    }

    void fw(realtype *w, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl, const realtype *spl, bool include_static) override {
    }

    void fx0(realtype *x0, const realtype t, const realtype *p, const realtype *k) override {
        x0_model_events(x0, t, p, k);
    }

    void fxdot(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w) override {
        xdot_model_events(xdot, t, x, p, k, h, w);
    }

    void fy(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w) override {
        y_model_events(y, t, x, p, k, h, w);
    }

    void fz(double *z, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
        z_model_events(z, ie, t, x, p, k, h);
    }

};

} // namespace model_model_events

} // namespace amici

#endif /* _amici_model_events_h */
