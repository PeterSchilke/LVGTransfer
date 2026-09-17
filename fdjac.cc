
#include <iostream>
#include "Mols.h"
#define NRANSI
#include "nrutil.h"
#define EPS 1.0e-4

void fdjac(int n, double x[], Transitions& thisMol, Cloud& thisCloud, double fvec[], double **df,
//	void (*vecfunc)(int, double [],  Transitions&, Cloud&, double [], char*), 
char* bo)
{
	int i,j;
	double h,temp,*f;
	void calEq(int, double [], Transitions&, Cloud&, double [], char*);

//	cout << "fdjac: bo= " << *bo << endl;
	fflush(stdout);
//    cout << "in fdjac 1: n = " << x[1] << " " << x[0] << " " << x[n] << endl;
	
	f=vector(1,n);
	for (j=1;j<=n;j++) {
		temp=x[j];
		h=EPS*fabs(temp);
		if (h == 0.0) h=EPS;
		x[j]=temp+h;
		h=x[j]-temp;
//		cout << f[0] << " " << f[1] << endl;
		calEq(n,x,thisMol,thisCloud,f,bo);
		x[j]=temp;
		for (i=1;i<=n;i++) df[i][j]=(f[i]-fvec[i])/h;
	}
//    cout << "in fdjac 2: n = " << x[1] << " " << x[0] << " " << x[n] << endl;

	free_vector(f,1,n);
}
#undef EPS
#undef NRANSI
