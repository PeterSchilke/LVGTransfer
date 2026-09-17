//
// LinearVib.cc	-- Peter Schilke Wed Feb 12 1997
//
//  Time-stamp: <2005-12-29 18:26:56 schilke> 
//

#include <iostream>
#include <fstream>
#include <string>
#include "Mols.h"
//atomicOxygen
atomicOxygen::atomicOxygen(int size, string MolFile, string ColFile,
		     string OutFile, string PlotFile, double *dipole, double R_c)
{
    Rc = R_c;
    Number_Of_Levels = size;  size++;
    Energy_Of_Level = new double[size];
    J_Of_Level      = new int[size];
    g_Of_Level      = new double[size];
    n_Of_Level      = new double[size];
    b_Of_Level      = new double[size];
#ifdef BLITZ
    Frequency.resize(size,size);
    Einstein_A.resize(size,size);
    Einstein_B.resize(size,size);
    P.resize(size,size);
#endif
    ifstream inMolFile (MolFile.c_str(), ios::in);
    if (! inMolFile)  // open failed 
	{
	    throw FileNotFoundError(MolFile.c_str());
	}
    
    int i=0, f=0;
    
        
// now read in the molecular data
    Jmax = 0;
    cout << "Reading molecular data...";
    do {
	inMolFile >> J_Of_Level[i] >> Energy_Of_Level[i];
//	cout <<  v_Of_Level[i] << " " <<  J_Of_Level[i] << " " Energy_Of_Level[i] << endl;
	g_Of_Level[i] = 2*J_Of_Level[i]+1;
	index_J[J_Of_Level[i]] = i;
	n_Of_Level[i] = 0;
	if (J_Of_Level[i] > Jmax) Jmax= J_Of_Level[i];
	i++;
    } while (!inMolFile.eof() && i < size);
    cout << "finished!" << endl;
    n_Of_Level[0] = 1;  // everything in ground state

// check if number of read energy levels is smaller than requested...    
    if (i < size) 
	{
	    // if yes, write a warning 
	    cout << "Using fewer levels than requested: "
		 << i-1 << " instead of " << size << endl;
	}
    Number_Of_Levels = i-1;
    

    // calculate Einstein-Coefficients
    for (i=0; i<Number_Of_Levels; i++)
	{
	    for (f=0; f<size; f++)
		{
#ifdef BLITZ
		    Frequency(i,f) = 0;
#else
		    Frequency[i][f] = 0;
#endif
		}
	}
    
	    
    cout << "Calculating Einstein Coefficients...";
    for (i=1; i<size; i++)
	{
	    for (f=0;f<i;f++)
		{
		    int Ji = J_Of_Level[i];
		    int Jf = J_Of_Level[f];
		    double ei = Energy_Of_Level[i];   // in cm-1
		    double ef = Energy_Of_Level[f];   // in cm-1

		    double freq = (ei-ef) * c_Light; // in Hz
#ifdef BLITZ
		    Frequency(i,f) = freq;
		    Frequency(f,i) = freq;
#else
		    Frequency[i][f] = freq;
		    Frequency[f][i] = freq;
#endif
		    if (Ji == 1 && Jf == 2)
#ifdef BLITZ
			Einstein_A(i,f) = 8.95e-5;
#else
			Einstein_A[i][f] = 8.95e-5;
#endif
		    else if (Ji == 0 && Jf == 2)
#ifdef BLITZ
			Einstein_A(i,f) = 1.00e-10;
#else
			Einstein_A[i][f] = 1.00e-10;
#endif
		    else if (Ji == 0 && Jf == 1)
#ifdef BLITZ
			Einstein_A(i,f) = 1.70e-5; 
#else
			Einstein_A[i][f] = 1.70e-5; 
#endif
		    else 
#ifdef BLITZ
			Einstein_A(i,f) = 0.0;
#else
			Einstein_A[i][f] = 0.0;
#endif
#ifdef BLITZ
		    Einstein_B(i,f) = Einstein_A(i,f)
			* c_Light*c_Light/(2*h_Planck*freq*freq*freq);
#else
		    Einstein_B[i][f] = Einstein_A[i][f]
			* c_Light*c_Light/(2*h_Planck*freq*freq*freq);
#endif
		    // absorption
		    double gi = g_Of_Level[i];
		    double gf = g_Of_Level[f];
#ifdef BLITZ
		    Einstein_B(f,i) = gi/gf * Einstein_B(i,f); 
#else
		    Einstein_B[f][i] = gi/gf * Einstein_B[i][f]; 
#endif
		}
	}
    cout << "finished!" << endl;
    
    // now take care of collisions
    // that makes arrays [size][maxLev] 
//    **CollRates  = new double[size];     // don't know why this doesn't work
//    double CollRates[maxLev][maxLev][maxTemp];
    
    ifstream inColFile (ColFile.c_str(), ios::in);
    if (! inColFile)  // open failed 
	{
	    throw FileNotFoundError(ColFile.c_str());
	}
    // read: first line temperatures
    cout << "Reading temperatures...";
    inColFile >> N_temp;
//    cout << N_temp << " " << size << endl;
#ifdef BLITZ
    CollRates.resize(size,size,N_temp);
    Collisions.resize(size,size);
    Collisions_e.resize(size,size);
    Temperature.resize(N_temp);
#endif
    for (i=0; i<N_temp; i++)
	{
#ifdef BLITZ
	    inColFile >> Temperature(i);
	    cout << Temperature(i) << " ";
#else
	    inColFile >> Temperature[i];
	    cout << Temperature[i] << " ";
#endif
	}
    cout << " finished!" << endl;
    int Ji, Jf;
    int index_i, index_f;
    cout << "Reading collision rates...";
    do
	{
	    // read Ji and Jf 
	    inColFile >> Ji >> Jf;
//	    cout << Ji << " " << Jf << " ";
	    // get the indices - using v=0
	    index_i = index_J[Ji];
	    index_f = index_J[Jf];
//	    cout << index_i << " " << index_f << " " << Number_Of_Levels << endl;
	    // read the whole thing in
	    if (Ji <= Jmax && Jf <= Jmax && index_i != index_f) 
		{
		    for (i=0; i<N_temp; i++)
			{
//			    cout << i << " " << index_i << " " << index_f << " in 1" << endl;
#ifdef BLITZ
			    inColFile >> CollRates(index_i,index_f,i);
#else
			    inColFile >> CollRates[index_i][index_f][i];
#endif
//			    cout << CollRates[index_i][index_f][i] << " ";
			}
//		    cout << endl;
		}
	    else
		{
		    for (i=0; i<N_temp; i++)
			{
			    double dat;
//			    cout << "x";
//			    cout << i << " in 1" << endl;
			    inColFile >>  dat;
//			    cout << dat << " ";
			}
//		    cout << endl;
		}
	} while (!inColFile.eof());
    cout << "finished!" << endl;
    outFile.open (OutFile.c_str(), ios::out);
    if (! outFile)  // open failed 
	{
	    string mess;
	    mess = "Cannot open " + OutFile + " for output";
	    throw mess.c_str();
	}
    plotFile.open (PlotFile.c_str(), ios::out);
    if (! plotFile)  // open failed 
	{
	    string mess;
	    mess = "Cannot open " + PlotFile + " for output";
	    throw mess.c_str();
	} else 
	    {
		plotFile << "! Tkin n(H2) n(e) N(Mol) T(back) tau(100mic) W(back) T(e) EM W(HII) "  
			 << "tau(back)[1-0] T_l(back)[1-0] tau(HII)[1-0] T_l(HII)[1-0] tau(1-0) T_l(1-0) "
			 << "tau(back)[2-1] etc." << endl;
	    }
//    cout << Einstein_A << endl;
//    cout << Einstein_B << endl;
//    cout << CollRates(Range::all(),Range::all(),1) << endl;
   
}


atomicOxygen::~atomicOxygen() 
{
    delete [] Energy_Of_Level;
    delete [] J_Of_Level;
    delete [] g_Of_Level;
    delete [] n_Of_Level;
}






