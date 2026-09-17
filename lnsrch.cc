
#include "Mols.h"
#include <iostream>
#define NRANSI
#include "nrutil.h"
#define ALF 1.0e-4
#define TOLX 1.0e-14//1.0e-7

void lnsrch(int n, double xold[], double fold, double g[], double p[], double x[],
	    Transitions& thisMol, Cloud& thisCloud,
	    double *f, double stpmax, int *check, char* bo)//, double (*func)(double [],  Transitions&, Cloud&))
{
	int i;
	double fmin(int, double[], Transitions&, Cloud&, char*);
	double a,alam,alam2,alamin,b,disc,f2,fold2,rhs1,rhs2,slope,sum,temp,
		test,tmplam;
	// cout << "ln:1: " << x[1] << " " << x[2] << " " << x[3] << endl;

	*check=0;
	for (sum=0.0,i=1;i<=n;i++) sum += p[i]*p[i];
	sum=sqrt(sum);
	if (sum > stpmax)
		for (i=1;i<=n;i++) p[i] *= stpmax/sum;
	for (slope=0.0,i=1;i<=n;i++)
		slope += g[i]*p[i];
	test=0.0;
	for (i=1;i<=n;i++) {
	    
		temp=fabs(p[i])/FMAX(fabs(xold[i]),1.0);
//		cout << "p[" << i << "] = " << p[i] << ", xold[" << i << "] = " << xold[i] << " temp = " << temp  << endl;
		
//		temp=fabs(p[i])/fabs(xold[i]);
		if (temp > test) test=temp;
	}
	alamin=TOLX/test;
	alam=1.0;
	for (;;) {
//	    cout << "alam: " << alam << endl;
//	    cout << "ln:2: " << x[1] << " " << x[2] << " " << x[3] << endl;
//	    cout << "ln:2: " << xold[1] << " " << xold[2] << " " << xold[3] << endl;
//	    cout << "ln:2: " << p[1] << " " << p[2] << " " << p[3] << " " << alam << endl;
	    for (i=1;i<=n;i++) x[i]=xold[i]+alam*p[i];
	    // cout << "ln:3: " << x[1] << " " << x[2] << " " << x[3] << endl;
		*f=fmin(n,x,thisMol,thisCloud,bo);
		if (alam < alamin) {
			for (i=1;i<=n;i++) x[i]=xold[i];
			*check=1;
			return;
		} else if (*f <= fold+ALF*alam*slope) return;
		else {
			if (alam == 1.0)
				tmplam = -slope/(2.0*(*f-fold-slope));
			else {
				rhs1 = *f-fold-alam*slope;
				rhs2=f2-fold2-alam2*slope;
				a=(rhs1/(alam*alam)-rhs2/(alam2*alam2))/(alam-alam2);
				b=(-alam2*rhs1/(alam*alam)+alam*rhs2/(alam2*alam2))/(alam-alam2);
				if (a == 0.0) tmplam = -slope/(2.0*b);
				else {
					disc=b*b-3.0*a*slope;
					if (disc<0.0) nrerror("Roundoff problem in lnsrch.");
					else tmplam=(-b+sqrt(disc))/(3.0*a);
				}
				if (tmplam>0.5*alam)
					tmplam=0.5*alam;
			}
		}
		alam2=alam;
		f2 = *f;
		fold2=fold;
		alam=FMAX(tmplam,0.1*alam);
	}
}
#undef ALF
#undef TOLX
#undef NRANSI
