//
// main.cc	-- Peter Schilke Mon Feb 10 1997
//
//  Time-stamp: <2007-11-14 11:38:49 schilke> 
//

//#include <stdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Mols.h"
#include "extra.h"

using namespace std;




int main()
{
     
    string Mol, MolFile, SifFile, ColFile, Type, PlotFile, OutFile;
    int Ntemp;
    char sl = 's';
    char bo = 'b';

    double dipole[maxVib*(maxVib+1)/2], Rc;
    cout << endl << BOLD << "\tWelcome to lvg - Peter Schilke 9/97" << OFF << endl << endl;
    cout << "\tsupported molecules:" << BOLD << " CO 13CO C18O SiO CS HCO+ DCO+" << OFF << endl;
    cout << "\t                    " << BOLD << " HCN HNC DCN DCN_hfs HC3N OI CI   " << OFF << endl;
    cout << "\t                    " << BOLD << " NH3-p NH3-o H2CO-p H2CO-o" << OFF << endl;
    cout << "\t                    " << BOLD << " CH3OH-A CH3OH-E" << OFF << endl;
    cout << "\tData in directory" << BOLD << " LVG_Data" << OFF << endl;
    
    cout << endl << "Defining molecule:" << endl;
    do 
	{
	    cout << "\tMolecule: ";
	    cin >> Mol;
            // defining the molecule - gives error if it doesn't know it
	}  while (Defmol(Mol, MolFile, ColFile, OutFile, PlotFile, SifFile, Type, dipole, Rc));
//    cout << "Files: " << MolFile << " " << ColFile << " " << SifFile << endl;

// now define the size - no check here, but later on
    int size;
    if ( Type.c_str() == "atomicOxygen") 
	{
	    size = 3;
	}
    else
	{
	    cout << "\tNumber of Levels: ";
	    cin >> size;
	}
    
    cout << "\tInit <b>oltzmann or <o>ptically thin? ";
    cin >> bo;
    cout << "\tMode: <s>ingle or <l>oop? ";
    cin >> sl;
    
    cout << "Type: " << Type.c_str() << endl;
    

    try 
	{
	    Cloud thisCloud;
	    
	    if (Type == "LinearVib") 
		{
		    // defining molecular parameters

		    LinearVib thisMol(size,MolFile,ColFile,OutFile,PlotFile,dipole,Rc);
		    thisMol.setMolName(Mol);
		    thisMol.printPars();
		    thisMol.DoCalc(thisCloud, sl, &bo);
		}
	    else if (Type == "LinearVibl") 
		{
		    // defining molecular parameters

		    LinearVibl thisMol(size,MolFile,ColFile,OutFile,PlotFile,dipole,Rc);
		    thisMol.setMolName(Mol);
		    thisMol.printPars();
		    thisMol.DoCalc(thisCloud, sl, &bo);
		}
	    else if (Type == "atomicOxygen") 
		{
		    // defining molecular parameters

		    atomicOxygen thisMol(size,MolFile,ColFile,OutFile,PlotFile,dipole,Rc);
		    thisMol.setMolName(Mol);
		    thisMol.printPars();
		    thisMol.DoCalc(thisCloud, sl, &bo);
		}
	    else if (Type == "atomicCarbon") 
		{
		    // defining molecular parameters

		    atomicCarbon thisMol(size,MolFile,ColFile,OutFile,PlotFile,dipole,Rc);
		    thisMol.setMolName(Mol);
		    thisMol.printPars();
		    thisMol.DoCalc(thisCloud, sl, &bo);
		}
	    else if (Type == "NH3") 
		{
		    // defining molecular parameters

		    NH3 thisMol(size,MolFile,ColFile,OutFile,PlotFile,dipole,Rc);
		    thisMol.setMolName(Mol);
		    thisMol.printPars();
		    thisMol.DoCalc(thisCloud, sl, &bo);
		}
	    else if (Type == "AsymmetricRotor") 
		{

		    // defining molecular parameters
		    AsymmetricRotor thisMol(size,MolFile,ColFile,OutFile,PlotFile,SifFile,dipole,Rc);
		    thisMol.setMolName(Mol);
		    thisMol.printPars();
//		    cout << "main - entering DoCalc\n";
		    thisMol.DoCalc(thisCloud, sl, &bo);
		}
	    else if (Type == "AsymmetricRotorT") 
		{
		    // defining molecular parameters

		    AsymmetricRotorT thisMol(size,MolFile,ColFile,OutFile,PlotFile,SifFile,dipole,Rc);
		    thisMol.setMolName(Mol);
		    thisMol.printPars();
//		    cout << "main - entering DoCalc\n";
		    thisMol.DoCalc(thisCloud, sl, &bo);
		}
	    else 
		{
		    throw "PANIC - this can't happen!";
//		    cout <<  "PANIC - this can't happen!" << endl;
		}
	}
    
    catch (const char *message) 
	{
	    cout << message << endl;
	    return -1;
	}
    catch(FileNotFoundError &e)
	{
	    cerr << endl << "FileNotFoundError: "
		 << e.messFileNotFoundError() << endl;
	}
    catch(VectorRangeError &e)
	{
	    cerr << endl << "VectorRangeError caught bad subscript = ["
		 << e.badVectorSubscript()  << "]" << endl;
	}
    catch(MatrixRangeError &e)
	{
	    cerr  << endl << "MatrixRangeError caught bad subscript = ["
		 << e.badMatrixSubscript(1) << "," << e.badMatrixSubscript(2) << "]" << endl;
	}
    return 1;
}


