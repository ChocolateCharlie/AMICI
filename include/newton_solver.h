#ifndef newton_solver
#define newton_solver

#include <sundials/sundials_dense.h>
#include <nvector/nvector_serial.h> // DlsMat
#include <sundials/sundials_sparse.h> // SlsMat
#include <klu.h>

class NewtonSolverDense;
class NewtonSolverSparse;
class NewtonSolverIterative;
class UserData;
class ReturnData;
class TempData;
class Model;

/**
 * @brief The NewtonSolver class sets up the linear solver for the Newton method.
 */

class NewtonSolver {
    
public:
    NewtonSolver(Model *model, ReturnData *rdata, UserData *udata, TempData *tdata);
    
    static NewtonSolver* getSolver(int linsolType, Model *model, ReturnData *rdata, UserData *udata, TempData *tdata, int *status);

    int getStep(int ntry, int nnewt, N_Vector delta);
    
    int getSensis(int it);
    
    virtual int prepareLinearSystem(int ntry, int nnewt) = 0;

    virtual int solveLinearSystem(N_Vector rhs) = 0;
    
    virtual ~NewtonSolver();
    
protected:
    Model *model;
    ReturnData *rdata;
    UserData *udata;
    TempData *tdata;
};



class NewtonSolverDense : public NewtonSolver {
    
public:
    NewtonSolverDense(Model *model, ReturnData *rdata, UserData *udata, TempData *tdata);
    int getStep(int ntry, int nnewt, N_Vector delta);
    int getSensis(int it);
    int solveLinearSystem(N_Vector rhs);
    int prepareLinearSystem(int ntry, int nnewt);
    ~NewtonSolverDense();
    
private:
    long int *pivots;
    N_Vector tmp1;
    N_Vector tmp2;
    N_Vector tmp3;
};



class NewtonSolverSparse : public NewtonSolver {
    
public:
    NewtonSolverSparse(Model *model, ReturnData *rdata, UserData *udata, TempData *tdata);
    int getStep(int ntry, int nnewt, N_Vector delta);
    int getSensis(int it);
    int solveLinearSystem(N_Vector rhs);
    int prepareLinearSystem(int ntry, int nnewt);
    ~NewtonSolverSparse();
    
private:
    N_Vector tmp1;
    N_Vector tmp2;
    N_Vector tmp3;
    klu_common common;
    klu_symbolic *symbolic;
    klu_numeric *numeric;
    int klu_status = 0;
};



class NewtonSolverIterative : public NewtonSolver {
    
public:
    NewtonSolverIterative(Model *model, ReturnData *rdata, UserData *udata, TempData *tdata);
    int getStep(int ntry, int nnewt, N_Vector delta);
    int getSensis(int it);
    int solveLinearSystem(N_Vector rhs);
    int prepareLinearSystem(int ntry, int nnewt);
    ~NewtonSolverIterative();
    
private:
    int newton_try;
    int i_newton;
};

#endif // NEWTON_SOLVER