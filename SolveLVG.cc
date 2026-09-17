//
// SolveLVG.cc	-- Peter Schilke Tue Mar  4 1997
//
//  Time-stamp: <2009-01-30 10:48:08 schilke> 
//

#include <iostream>
#include "Mols.h"
#include "extra.h"

void Transitions::SolveLVG(Cloud &thisCloud, char* bo)
{
//    cout << "SolveLVG: bo= " << *bo << endl;

    
    int newt(double [], Transitions&, Cloud&, int, int*,
	     //void (*)(int, double [], Transitions&, Cloud&, double[], char*), 
	     char*);
//    void calEq(int, double [], Transitions&, Cloud&, double [], char*);
    int check=0, its = -1;
//    this.setP(thisCloud);
// initializing n
    const int niter_max = 10;
    int niter = 0, negflag = 0;
    double T_guess = thisCloud.Tkin();
    while (++niter < niter_max && (its == -1 || check == 1 || negflag == 1)) 
	{
	    double nsum = 1;
	    double bsum = 1;

	    n_Of_Level[0] = 1.;
	    b_Of_Level[0] = 1.;

	    for (int i=1; i<Number_Of_Levels; i++) {
		n_Of_Level[i] = 0;
		double Ji = J_Of_Level[i];
		double Ei = Energy_Of_Level[i];   // in cm-1
		double E0 = Energy_Of_Level[0];   // in cm-1
		double E_level = (Ei-E0) * c_Light * 1e-9 * GHzToK;  // in Hz
		double gi = g_Of_Level[i];
		n_Of_Level[i] = gi * exp(-E_level/T_guess);
		b_Of_Level[i] = 1;
//	cout << "i: " << i << " " << E_level << " " << n_Of_Level[i] << endl;
		nsum += n_Of_Level[i];
		bsum++;
	    }
	    n_Of_Level[Number_Of_Levels] = nsum;
	    b_Of_Level[Number_Of_Levels] = bsum;

//	    for (int i=0; i<=Number_Of_Levels; i++) {
//		cout << "i: " << i << " "  << n_Of_Level[i] << endl;
//    }
	    
// solving
	    
	    cout << "\nworking..." << endl;
	    
//	    cout << "entering newt: " << b_Of_Level[1] << endl;
//	    cout << "entering newt" << endl;
/*	    cout << endl;
	    for (int i=0;  i < Number_Of_Levels; i++) 
		{
		    cout << "before: i: " << i << " " << b_Of_Level[i] << endl;
		}
	    
*/				
	    its = newt(b_Of_Level-1, *this, thisCloud, Number_Of_Levels, &check, bo);
/*
	    cout << endl;
	    for (int i=0;  i < Number_Of_Levels; i++) 
		{
		    cout << "after : i: " << i << " " << b_Of_Level[i] << endl;
		}
*/
/*
	    if (niter == 1) 
		{
		    cout << endl;
		    
		    for (int i=0; i < Number_Of_Levels; i++)
			{
			    for (int j=0; j < Number_Of_Levels; j++) 
				{
				    cout << " i: " << i << " j: " << j << " P(i,j): " << this->getP(i,j) << endl;
				}
			}
		}
*/	    
//	    cout << "exiting newt: " << b_Of_Level[1] << endl;
	    negflag = 0;
	    bsum = 0;
	    for (int i=0; i<Number_Of_Levels; i++) {
		if (b_Of_Level[i] <=0 ) 
		    {
				negflag = 1;
			cout << endl << "WARNING: negative population in level " << i;
//			break;   // get out of here
			b_Of_Level[i] = 1e-10;
			 
		    }
		bsum++;
	    }
	    b_Of_Level[Number_Of_Levels] = bsum;
	    
	    if (its == -1 || check == 1 || negflag == 1)
// its -1: exceeded maximum number of iterations
// check 1: converged to local minimum
		{
		    T_guess *= 0.9;
		    cout << "\nRestart with T_guess = " << T_guess
			 << " after " << niter << " cycles, its = "
			 << its << ", check = " << check << ", negflag = " << negflag << endl;
		}
	}
		    
    if (niter == niter_max) 
	{
	    cout << "\nno Convergence after " << BOLD << niter << OFF << " cycles" << endl;
	    Convergence = 0;
	}
    else 
	{
	    cout << "\n\nConvergence after " << BOLD << its << OFF << " iterations "
		 << " and " << BOLD << niter-1 << OFF << " cycles" << endl;
	    if (check == -1) 
		{
		    cout << "function value convergence" << endl;
		}
	    else if (check == -2) 
		{
		    cout << "step size convergence"  << endl;
		}
	    else if (check == -3)
		{
		    cout << "step size convergence in lnsrch" << endl;
		}
	    else if (check == 0)
		{
		    cout << "function value convergence in lnsrch" << endl;
		}
	    else
		{
		    cout << "Huh? This can't happen: check = " << check << endl;
		}
	    Convergence = 1;
	}
}

