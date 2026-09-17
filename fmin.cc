#define NRANSI
#include "nrutil.h"
#include "Mols.h"

//extern int nn;
extern double *fvec;
//extern void (*nrfuncv)(int n, double v[],  Transitions&, Cloud&, double f[]);

double fmin(int n, double x[],  Transitions& thisMol, Cloud& thisCloud,char* bo)
{
    
    void calEq(int, double [], Transitions&, Cloud&, double [], char*);

    int i;
    double sum;
//	cout << "fmin: " << x[1] << " " << x[2] << endl;
//    cout << "in fmin 1: n = " << x[1] << " " << x[0] << " " << x[n] << endl;
    calEq(n,x,thisMol,thisCloud,fvec,bo);
//    cout << "in fmin 1: n = " << x[1] << " " << x[0] << " " << x[n] << endl;
    for (sum=0.0,i=1;i<=n;i++) sum += SQR(fvec[i]);
    return 0.5*sum;
}
#undef NRANSI
