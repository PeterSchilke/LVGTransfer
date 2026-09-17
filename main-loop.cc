//
// main.cc	-- Peter Schilke Mon Feb 10 1997
//
//  Time-stamp: <97/09/01 16:36:27 schilke> 
//

#include <iostream>
#include <iomanip>
#include <strings>
#include "Mols.h"
#include "extra.h"

int main()
{
    
    char Mol[ string_size ], MolFile[ string_size ],
	 ColFile[ string_size ], Type[ string_size ];
    int Ntemp;
    char yn = 'y';
    double dipole[maxVib*(maxVib+1)/2];
    cout << endl << "Defining molecule:" << endl;
    do 
	{
	    cout << "\tMolecule: ";
	    cin >> Mol;
            // defining the molecule - gives error if it doesn't know it
	}  while (Defmol(Mol, MolFile, ColFile, Type , Ntemp, dipole));
//    cout << MolFile << " " << ColFile << endl;

// now define the size - no check here, but later on
    int size;
    cout << "\tSize: ";
    cin >> size;

    try 
	{
	    if (strcmp(Type, "LinearVib") == 0) 
		{
		    // defining molecular parameters
		    LinearVib thisMol(size,Ntemp,MolFile,ColFile,dipole);
		    // defining cloud parameters
		    do 
			{
			    Cloud thisCloud;
			    // calculating collision coefficients
			    thisMol.CalcColl(thisCloud);
			    // solving the LVG
			    thisMol.SolveLVG(thisCloud);
			    // printing out
			    thisMol.PrintOut(thisCloud);
			    cout << "\nContinue " << BOLD << "<y/n>" << OFF << " ? ";
			    cin >> yn;
			}
		    while (yn == 'y');
		    
//		    print(thisMol); // overloaded function to print everything
		}
	    else 
		{
		    cout << "PANIC - this can't happen!" << endl;
		    return -1;
		}
		    
		
	}
    
    catch (const char *message) 
	{
	    cout << message << endl;
	    return -1;
	}
    catch(VectorRangeError e)
	{
	    cerr << endl << "VectorRangeError caught bad subscript = ["
		 << e.badVectorSubscript()  << "]" << endl;
	}
    catch(MatrixRangeError e)
	{
	    cerr  << endl << "MatrixRangeError caught bad subscript = ["
		 << e.badMatrixSubscript(1) << "," << e.badMatrixSubscript(2) << "]" << endl;
	}
    return 1;
}


