#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>

#define ERR_REL 1.0e-05
#define ERR_ABS 1.0e-05
#define LIMIT_SIZE 1000                                                 /* Cantidad máxima de subintervalos */
#define INT_RULE GSL_INTEG_GAUSS41                                      /* Regla de integración de Gauss-Kronrod para 15, 21, 31, 41, 51 o 61 puntos */

double qag(double a, double b, double (* func)(double, void *)){

        int i, times, status;
        gsl_function f;
        gsl_integration_workspace *workspace;
        double ret, ret_abserr;

        f.function = func;
        f.params = 0;

        workspace = gsl_integration_workspace_alloc(LIMIT_SIZE);
        gsl_integration_qag(&f, a, b, ERR_REL, ERR_ABS, LIMIT_SIZE, INT_RULE, workspace, &ret, &ret_abserr);
        gsl_integration_workspace_free(workspace);

        return ret;
        
}