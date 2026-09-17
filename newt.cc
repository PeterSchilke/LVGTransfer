
#include "Mols.h"
#include <iostream>
#define NRANSI
#include "nrutil.h"
#define MAXITS 200
#define TOLF 1e-8 // 1e-4
#define TOLMIN 1e-12//1.0e-6
#define TOLX 1.0e-7
#define STPMX 100.0
#define ITSMIN 3

int nn;
double *fvec;
//void (*nrfuncv)(int n, double v[],  Transitions& thisMol, Cloud& thisCloud, double f[], char bo);
#define FREERETURN {free_vector(fvec,1,n);free_vector(xold,1,n);\
	free_vector(p,1,n);free_vector(g,1,n);free_matrix(fjac,1,n,1,n);\
	free_ivector(indx,1,n);return its;}

int newt(double x[], Transitions& thisMol, Cloud& thisCloud, int n, int *check, 
	 //void (*vecfunc)(int, double [], Transitions&, Cloud&, double [], char), 
	 char* bo)
{
	void fdjac(int n, double x[],  Transitions&, Cloud&, double fvec[], double **df,
//		void (*vecfunc)(int, double [],  Transitions&, Cloud&, double [], char), 
		   char*);
	double fmin(int n, double x[],  Transitions&, Cloud&, char*);
	void lnsrch(int n, double xold[], double fold, double g[], double p[], double x[],
		     Transitions&, Cloud&,
		    double *f, double stpmax, int *check, char* bo);//double (*func)(double [],  Transitions&, Cloud&));
	void lubksb(double **a, int n, int *indx, double b[]);
	void ludcmp(double **a, int n, int *indx, double *d);
	void calEq(int, double [], Transitions&, Cloud&, double [], char*);
	int i,j,its=1,*indx;
	double d,den,f,fold,stpmax,sum,temp,test,scale,**fjac,*g,*p,*xold;

//	cout << "newt: bo= " << *bo << endl;

	indx=ivector(1,n);
	fjac=matrix(1,n,1,n);
	g=vector(1,n);
	p=vector(1,n);
	xold=vector(1,n);
	fvec=vector(1,n);
	nn=n;
//	cout << endl;
	
        calEq(n,x,thisMol,thisCloud,fvec,bo);

	f=fmin(n,x,thisMol,thisCloud,bo);
	test=0.0;
	scale = 0;

// set scale for function values
	for (i=1;i<n;i++)
		if (fabs(fvec[i]) > scale) scale=fabs(fvec[i]);
	if (scale<1e-8*TOLF) {
	    *check = 0;
	    cout << "in newt: scale = " << scale << endl;
	    FREERETURN;
	}
	
	for (sum=0.0,i=1;i<=n;i++) sum += SQR(x[i]);
	stpmax=STPMX*FMAX(sqrt(sum),(double)n);
	for (its=1;its<=MAXITS;its++) {
	    cout << its << " " ;
	    fflush(stdout);
	    fdjac(n,x,thisMol,thisCloud,fvec,fjac,bo);
//		 cout << "3: " << its << " " << x[1] << " " << x[2] << " " << x[3] << endl;
	for (i=1;i<=n;i++) {
	    for (sum=0.0,j=1;j<=n;j++) sum += fjac[j][i]*fvec[j];
	    g[i]=sum;
	}
	for (i=1;i<=n;i++) xold[i]=x[i];
	fold=f;
	for (i=1;i<=n;i++) p[i] = -fvec[i];
//		 cout << "4: " << x[1] << " " << x[2] << " " << x[3] << endl;
//		 cout << "4o: " << xold[1] << " " << xold[2] << " " << xold[3] << endl;
//		 cout << "4: " << p[1] << " " << p[2] << " " << p[3] << endl;
	ludcmp(fjac,n,indx,&d);
//	cout << "6: " << p[1] << " " << p[2] << " " << p[3] << endl;
	lubksb(fjac,n,indx,p);
//	cout << "6: " << p[1] << " " << p[2] << " " << p[3] << endl;
	lnsrch(n,xold,fold,g,p,x,thisMol,thisCloud,&f,stpmax,check,bo);
//	cout << "5: " << p[1] << " " << p[2] << " " << p[3] << endl;
//		 cout << "5: " << x[1] << " " << x[2] << " " << x[3] << endl;
	test=0.0;
	// use as test values function values scaled by first maximum
	for (i=1;i<n;i++)
	    if (fabs(fvec[i]/scale) > test) test=fabs(fvec[i]/scale);
	if (test < TOLF && its > ITSMIN) {
	    *check=-1;
	    FREERETURN;
	}
	// no checks for zero gradient or stepsize performed any more
/*		if (*check) {
		test=0.0;
		den=FMAX(f,0.5*n);
		for (i=1;i<=n;i++) {
		temp=fabs(g[i])*FMAX(fabs(x[i]),1.0)/den;
//				cout << "newt: temp[" << i << "] = " << temp << endl;

if (temp > test) test=temp;
}
*check=(test < TOLMIN ? 1 : -3);
FREERETURN
}
test=0.0;
for (i=1;i<=n;i++) {
temp=(fabs(x[i]-xold[i]))/FMAX(fabs(x[i]),1.0);
//			temp=(fabs(x[i]-xold[i]))/fabs(x[i]+xold[i]);
//			cout << "newt: temp[" << i << "] = " << temp << endl;
if (temp > test) test=temp;
}
if (test < TOLX && its > 3) {
*check = -2; FREERETURN;
}
*/
	}
	its = -1;
	FREERETURN;
	nrerror("MAXITS exceeded in newt"); 
}
#undef MAXITS
#undef TOLF
#undef TOLMIN
#undef TOLX
#undef STPMX
#undef FREERETURN
#undef NRANSI
#undef ITSMIN
