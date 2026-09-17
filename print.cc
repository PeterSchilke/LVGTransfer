//
// print.cc	-- Peter Schilke Tue Feb 11 1997
//
//  Time-stamp: <97/03/04 15:02:55 schilke> 
//

#include <iostream>
#include <iomanip>
#include "Mols.h"

void print(LinearVib &thisMol)
{
    int i;
    for (i=0; i<thisMol.NumberOfLevels(); i++) 
	{
	    cout << setiosflags(ios::fixed);
	    cout << setw(3) << i << ": ";
//	    cout << setw(3) << thisMol.v(i);
	    cout << setw(3) << setprecision(0) << thisMol.J(i);
	    cout << setw(3) << setprecision(0) << thisMol.g(i);
	    cout << setw(10) << setprecision(4) << thisMol.Energy(i);
	    cout << setw(10) << setprecision(4) << thisMol.n(i);
	    cout << endl;
	}
// print A
    cout << endl << "Einstein-A" << endl;
    cout.setf(ios::scientific, ios::floatfield);
    for (i=0;i<thisMol.NumberOfLevels(); i++)
	{
	    cout << setw(3) << i << " ";
	    for (int j=0;j<thisMol.NumberOfLevels(); j++)
		{
		    cout <<  setw(10) << setprecision(7) << thisMol.A(i,j) << " ";
		}
	    cout << endl;
	}
    
// print B
    cout << endl << "Einstein-B" << endl;
    for (i=0;i<thisMol.NumberOfLevels(); i++)
	{
	    cout << setw(3) << i << " ";
	    for (int j=0;j<thisMol.NumberOfLevels(); j++)
		{
		    cout <<  setw(10) << setprecision(7) << thisMol.B(i,j) << " ";;
		}
	    cout << endl;
	}
    
// print C
    cout << endl << "Collisions" << endl;
    for (i=0;i<thisMol.NumberOfLevels(); i++)
	{
	    cout << setw(3) << i << " ";
	    for (int j=0;j<thisMol.NumberOfLevels(); j++)
		{
		    cout <<  setw(10) << setprecision(7) << thisMol.C(i,j) << " ";;
		}
	    cout << endl;
	}
    
}

void print(const char* Type)
{
    cout << Type << endl;
}

