/* 
 * Time-stamp: <2006-11-27 17:26:07 schilke>
 *
 * test.c	-- Peter Schilke Thu Jun 26 1997 (<schilke@mpifr-bonn.mpg.de>)
 *
 */
#include <iostream>
#include "Mols.h"
#define NRANSI
#include "nrutil.h"

void calEq(int n, double x[],  Transitions& thisMol, Cloud& thisCloud, double f[], char *bo)
{
    double xsum = 0, xs = 0;
    int i,j;
//    cout << "calEq: bo= " << *bo << endl;

// normalizing n
//    cout << "in CalEq: n = " << x[1] << " " << x[0] << " " << x[n] << endl;
/*    for (i=1; i<=n; i++) 
	{ 
	    xsum += x[i]*thisMol.n(i-1);
	}
    xsum /= thisMol.getNorm();
    
    for (i=1; i<=n; i++) 
	{ 
	    x[i] /= xsum;
	    xs += x[i];
	    cout << i << " x[i]: " << x[i] << endl;
	    
	}
    x[n+1] = xs;
//    cout << " xsum, xs: " << xsum << " " << xs << " " << x[n+1] << endl;
*/
	    
    thisMol.setP(thisCloud,bo);
    for (i=0; i<n; i++) 
	{
	    f[i+1] = 0;
	    for (j=0; j<n; j++) 
		{
		    f[i+1] += thisMol.getP(i,j)*x[j+1]*thisMol.n(j);
//		    cout << "calEqp: " << i << "," << j << ": " <<
//			f[i+1] << " " << thisMol.n(j) << " " << x[j+1] << endl;
		    
		}
//	    cout << i << " " << f[i+1] << endl;
	}
/*
    f[n] = -x[n+1];
     for (j=0; j<n; j++) 
		{
		    f[n] += x[j+1];
		}
		*/
    return;
}
;
