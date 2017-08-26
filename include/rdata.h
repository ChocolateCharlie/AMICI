#ifndef _MY_RDATA
#define _MY_RDATA
#include <include/udata.h>
class UserData;
class Model;

/** @brief struct that stores all data which is later returned by the mex
 * function
 *
 * NOTE: MATLAB stores multidimensional arrays in column-major order
 * (FORTRAN-style)
 */
class ReturnData {
  public:
    ReturnData();

    ReturnData(const UserData *udata, const Model *model);

    virtual void setDefaults();

    /**
     * @brief performs all necessary actions to reset return data upon
     * integration failure
     * @param[in] udata pointer to the user data struct @type UserData
     */
    void invalidate();

    void setLikelihoodSensitivityFirstOrderNaN();
    void setLikelihoodSensitivitySecondOrderNaN();

    int
    applyChainRuleFactorToSimulationResults(const UserData *udata,
                                            const realtype *unscaledParameters);

    virtual ~ReturnData();

    /** timepoints (dimension: nt) */
    double *ts;

    /** time derivative (dimension: nx) */
    double *xdot;

    /** Jacobian of differential equation right hand side (dimension: nx x nx,
     * column-major) */
    double *J;

    /** event output (dimension: nmaxevent x nz, column-major) */
    double *z;

    /** event output sigma standard deviation (dimension: nmaxevent x nz,
     * column-major) */
    double *sigmaz;

    /** parameter derivative of event output (dimension: nmaxevent x nz,
     * column-major) */
    double *sz;

    /** parameter derivative of event output standard deviation (dimension:
     * nmaxevent x nz, column-major)  */
    double *ssigmaz;

    /** event trigger output (dimension: nmaxevent x nz, column-major)*/
    double *rz;

    /** parameter derivative of event trigger output (dimension: nmaxevent x nz
     * x nplist, column-major) */
    double *srz;

    /** second order parameter derivative of event trigger output (dimension:
     * nmaxevent x nztrue x nplist x nplist, column-major) */
    double *s2rz;

    /** state (dimension: nt x nx, column-major) */
    double *x;

    /** parameter derivative of state (dimension: nt x nx x nplist,
     * column-major) */
    double *sx;

    /** observable (dimension: nt x ny, column-major) */
    double *y;

    /** observable standard deviation (dimension: nt x ny, column-major) */
    double *sigmay;

    /** parameter derivative of observable (dimension: nt x ny x nplist,
     * column-major) */
    double *sy;

    /** parameter derivative of observable standard deviation (dimension: nt x
     * ny x nplist, column-major) */
    double *ssigmay;

    /** number of integration steps forward problem (dimension: nt) */
    double *numsteps;

    /** number of integration steps backward problem (dimension: nt) */
    double *numstepsB;

    /** number of right hand side evaluations forward problem (dimension: nt) */
    double *numrhsevals;

    /** number of right hand side evaluations backwad problem (dimension: nt) */
    double *numrhsevalsB;

    /** number of error test failures forward problem (dimension: nt) */
    double *numerrtestfails;

    /** number of error test failures backwad problem (dimension: nt) */
    double *numerrtestfailsB;

    /** number of linear solver convergence failures forward problem (dimension:
     * nt) */
    double *numnonlinsolvconvfails;

    /** number of linear solver convergence failures backwad problem (dimension:
     * nt) */
    double *numnonlinsolvconvfailsB;

    /** employed order forward problem (dimension: nt) */
    double *order;

    /** flag indicating success of Newton solver */
    double *newton_status;

    /* computation time of the Newton solver [s] */
    double *newton_time;

    /** number of Newton steps for steady state problem */
    double *newton_numsteps;

    /** number of linear steps by Newton step for steady state problem */
    double *newton_numlinsteps;

    /** steady state found be Newton solver */
    double *xss;

    /** likelihood value (double[1]) */
    double *llh;

    /** chi2 value (double[1]) */
    double *chi2;

    /** parameter derivative of likelihood (dimension: nplist) */
    double *sllh;

    /** second order parameter derivative of likelihood (dimension: (nJ-1) x
     * nplist, column-major) */
    double *s2llh;

    /** status code (double[1]) */
    double *status;

  protected:
    virtual void copyFromUserData(const UserData *udata);

    virtual void initFields();

    virtual void initField1(double **fieldPointer, const char *fieldName,
                            int dim);

    /**
     * @ brief initialise matrix and attach to the field
     * @ param FIELD name of the field to which the matrix will be attached
     * @ param D1 number of rows in the matrix
     * @ param D2 number of columns in the matrix
     */

    virtual void initField2(double **fieldPointer, const char *fieldName,
                            int dim1, int dim2);

    /**
     * @ brief initialise 3D tensor and attach to the field
     * @ param FIELD name of the field to which the tensor will be attached
     * @ param D1 number of rows in the tensor
     * @ param D2 number of columns in the tensor
     * @ param D3 number of elements in the third dimension of the tensor
     */

    virtual void initField3(double **fieldPointer, const char *fieldName,
                            int dim1, int dim2, int dim3);

    /**
     * @ brief initialise 4D tensor and attach to the field
     * @ param FIELD name of the field to which the tensor will be attached
     * @ param D1 number of rows in the tensor
     * @ param D2 number of columns in the tensor
     * @ param D3 number of elements in the third dimension of the tensor
     * @ param D4 number of elements in the fourth dimension of the tensor
     */

    virtual void initField4(double **fieldPointer, const char *fieldName,
                            int dim1, int dim2, int dim3, int dim4);

    bool freeFieldsOnDestruction;

  public:
    /** total number of model parameters */
    const int np;
    /** number of fixed parameters */
    const int nk;
    /** number of states */
    const int nx;
    /** number of states in the unaugmented system */
    const int nxtrue;
    /** number of observables */
    const int ny;
    /** number of observables in the unaugmented system */
    const int nytrue;
    /** number of event outputs */
    const int nz;
    /** number of event outputs in the unaugmented system */
    const int nztrue;
    /** number of events */
    const int ne;
    /** dimension of the augmented objective function for 2nd order ASA */
    const int nJ;

    const int nplist;
    const int nmaxevent;
    const int nt;
    const int newton_maxsteps;
    const AMICI_parameter_scaling pscale;
    const AMICI_o2mode o2mode;
    const AMICI_sensi_order sensi;
    const AMICI_sensi_meth sensi_meth;
};

#endif /* _MY_RDATA */
