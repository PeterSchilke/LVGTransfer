#include "Mols.h"

void lubksb(double **a, int n, int *indx, double b[])
{
	int i,ii=0,ip,j;
	double sum;

	for (i=1;i<=n;i++) {
		ip=indx[i];
		sum=b[ip];
//		cout << "ip, n, ii, b[i]: " << ip << " " << n << " " << " " << ii << " " << b[ip] << endl;
		
		b[ip]=b[i];
		if (ii)
			for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
		else if (sum) ii=i;
		b[i]=sum;
//		cout << "i, n, ii, b[i]: " << i << " " << n << " " << " " << ii << " " << b[i] << endl;
	}
	for (i=n;i>=1;i--) {
		sum=b[i];
		for (j=i+1;j<=n;j++) {
		    sum -= a[i][j]*b[j];
//		    cout << "i j a b " << i << " " << j << " " << a[i][j] << " " << b[j] << " " << b[i] << endl;
		}
		
		b[i]=sum/a[i][i];
//		cout << "i, n, ii, b[i]: " << i << " " << n << " " << " " << ii << " " << b[i] << endl << endl;
	}
}
