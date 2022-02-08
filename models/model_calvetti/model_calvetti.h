#ifndef _amici_model_calvetti_h
#define _amici_model_calvetti_h
#include <cmath>
#include <memory>
#include "amici/defines.h"
#include <sunmatrix/sunmatrix_sparse.h> //SUNMatrixContent_Sparse definition
#include "amici/solver_idas.h"
#include "amici/model_dae.h"

namespace amici {

class Solver;

namespace model_model_calvetti{

extern void JSparse_model_calvetti(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype cj, const realtype *dx, const realtype *w, const realtype *dwdx);
extern void Jy_model_calvetti(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void M_model_calvetti(realtype *M, const realtype t, const realtype *x, const realtype *p, const realtype *k);
extern void dJydsigma_model_calvetti(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dJydy_model_calvetti(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dwdx_model_calvetti(realtype *dwdx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl);
extern void dydx_model_calvetti(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void root_model_calvetti(realtype *root, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *dx);
extern void sigmay_model_calvetti(double *sigmay, const realtype t, const realtype *p, const realtype *k);
extern void w_model_calvetti(realtype *w, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl);
extern void x0_model_calvetti(realtype *x0, const realtype t, const realtype *p, const realtype *k);
extern void xdot_model_calvetti(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *dx, const realtype *w);
extern void y_model_calvetti(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w);

class Model_model_calvetti : public amici::Model_DAE {
public:
    Model_model_calvetti()
        : amici::Model_DAE(
              amici::ModelDimensions(
                  6,
                  6,
                  6,
                  6,
                  0,
                  0,
                  6,
                  6,
                  6,
                  0,
                  0,
                  4,
                  1,
                  38,
                  53,
                  0,
                  0,
                  0,
                  {},
                  26,
                  5,
                  3
              ),
              amici::SimulationParameters(
                  std::vector<realtype>(6, 1.0),
                  std::vector<realtype>(0, 1.0)
              ),
              amici::SecondOrderMode::none,
              std::vector<realtype>{1, 1, 1, 0, 0, 0},
              std::vector<int>{})
              {};

    amici::Model* clone() const override { return new Model_model_calvetti(*this); };

    std::string getAmiciCommit() const override { return "dc99fa1bcb04914008ba8ed39157513d443c3f43"; };

    void fJSparse(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype cj, const realtype *dx, const realtype *w, const realtype *dwdx) override {
        JSparse_model_calvetti(JSparse, t, x, p, k, h, cj, dx, w, dwdx);
    }

    void fJrz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    void fJy(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        Jy_model_calvetti(nllh, iy, p, k, y, sigmay, my);
    }

    void fJz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    void fM(realtype *M, const realtype t, const realtype *x, const realtype *p, const realtype *k) override {
        M_model_calvetti(M, t, x, p, k);
    }

    void fdJrzdsigma(double *dJrzdsigma, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    void fdJrzdz(double *dJrzdz, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    void fdJydsigma(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydsigma_model_calvetti(dJydsigma, iy, p, k, y, sigmay, my);
    }

    void fdJydy(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydy_model_calvetti(dJydy, iy, p, k, y, sigmay, my);
    }

    void fdJzdsigma(double *dJzdsigma, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    void fdJzdz(double *dJzdz, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    void fdeltaqB(double *deltaqB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB, const realtype *xBdot) override {
    }

    void fdeltasx(double *deltasx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *sx, const realtype *stau) override {
    }

    void fdeltax(double *deltax, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old) override {
    }

    void fdeltaxB(double *deltaxB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB, const realtype *xBdot) override {
    }

    void fdrzdp(double *drzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    void fdrzdx(double *drzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    void fdsigmaydp(double *dsigmaydp, const realtype t, const realtype *p, const realtype *k, const int ip) override {
    }

    void fdsigmazdp(double *dsigmazdp, const realtype t, const realtype *p, const realtype *k, const int ip) override {
    }

    void fdwdp(realtype *dwdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl, const realtype *stcl) override {
    }

    void fdwdx(realtype *dwdx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl) override {
        dwdx_model_calvetti(dwdx, t, x, p, k, h, w, tcl);
    }

    void fdxdotdp(realtype *dxdotdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *dx, const realtype *w, const realtype *dwdp) override {
    }

    void fdydp(double *dydp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp) override {
    }

    void fdydx(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        dydx_model_calvetti(dydx, t, x, p, k, h, w, dwdx);
    }

    void fdzdp(double *dzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    void fdzdx(double *dzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    void froot(realtype *root, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *dx) override {
        root_model_calvetti(root, t, x, p, k, h, dx);
    }

    void frz(double *rz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    void fsigmay(double *sigmay, const realtype t, const realtype *p, const realtype *k) override {
        sigmay_model_calvetti(sigmay, t, p, k);
    }

    void fsigmaz(double *sigmaz, const realtype t, const realtype *p, const realtype *k) override {
    }

    void fsrz(double *srz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
    }

    void fstau(double *stau, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip, const int ie) override {
    }

    void fsx0(realtype *sx0, const realtype t,const realtype *x0, const realtype *p, const realtype *k, const int ip) override {
    }

    void fsz(double *sz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
    }

    void fw(realtype *w, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl) override {
        w_model_calvetti(w, t, x, p, k, h, tcl);
    }

    void fx0(realtype *x0, const realtype t, const realtype *p, const realtype *k) override {
        x0_model_calvetti(x0, t, p, k);
    }

    void fxdot(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *dx, const realtype *w) override {
        xdot_model_calvetti(xdot, t, x, p, k, h, dx, w);
    }

    void fy(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w) override {
        y_model_calvetti(y, t, x, p, k, h, w);
    }

    void fz(double *z, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

};

} // namespace model_model_calvetti

} // namespace amici 

#endif /* _amici_model_calvetti_h */
