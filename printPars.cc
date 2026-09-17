//
// print.cc	-- Peter Schilke Tue Feb 11 1997
//
//  Time-stamp: <2006-11-24 16:14:52 schilke> 
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Mols.h"

void Transitions::printPars()
{
    cout << "MolName " << this->MolName() << endl;
    string ParFile;
    ParFile = this->MolName() + ".parameters";
    ofstream outParFile;
    outParFile.open (ParFile.c_str(), ios::out);

    outParFile << "Calculation for Molecule " << this->MolName() << " with " << this->NumberOfLevels() << " levels." 
	    << endl << endl;

    for (int i=0; i<this->NumberOfLevels(); i++) 
	{
	    for (int j=0; j<i; j++) 
		{
		    if (this->A(i,j) != 0) 
			{
			    outParFile.setf(ios::basefield);
			    outParFile << setw(4) << i << " " << j << " ";
//	    outParFile << setw(3) << this->v(i);
			    outParFile << setw(4) << setprecision(0) << this->J(i) << " ";
			    outParFile << setw(4) << setprecision(0) << (int)this->g(i) << " ";
			    outParFile << setw(4) << setprecision(0) << this->J(j) << " ";
			    outParFile << setw(4) << setprecision(0) << (int)this->g(j) << " ";
			    outParFile.setf(ios::fixed, ios::floatfield);
			    outParFile << setw(10) << setprecision(4) << this->Energy(i) << " ";
			    outParFile <<  setw(12) << setprecision(7) << this->frequency(i,j)*1e-9 << " ";
			    outParFile.setf(ios::scientific, ios::floatfield);
			    outParFile <<  setw(10) << setprecision(7) << this->A(i,j) << endl;
			}
		}
	}
}
