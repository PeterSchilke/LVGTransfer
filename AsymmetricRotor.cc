//
// NH3.cc	-- Peter Schilke Wed Feb 12 1997
//
//  Time-stamp: <2008-02-13 13:13:14 schilke> 
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Mols.h"
//LinearVib
AsymmetricRotor::AsymmetricRotor(int size, string MolFile, string ColFile,
				 string OutFile, string PlotFile, string SifFile,  
				 double *dipole,double R_c) 
{
    Rc = R_c;
    Number_Of_Levels = size;  size++;
    Energy_Of_Level = new double[size];
    J_Of_Level      = new int[size];
    Kp_Of_Level     = new int[size];
    Km_Of_Level     = new int[size];
    g_Of_Level      = new double[size];
    n_Of_Level      = new double[size];
    b_Of_Level      = new double[size];
#ifdef BLITZ
    Frequency.resize(size,size);
    Einstein_A.resize(size,size);
    Einstein_B.resize(size,size);
    P.resize(size,size);
    S_if.resize(size,size);
#endif
    int i, f;
    for (i = 0; i < maxVib*(maxVib+1)/2; i++)
	{
	    mu[i] = dipole[i];
	}

    ifstream inSifFile (SifFile.c_str(), ios::in);
    if (! inSifFile)  // open failed 
	{
	    throw FileNotFoundError(SifFile.c_str());
	}
    
    ifstream inMolFile (MolFile.c_str(), ios::in);
    if (! inMolFile)  // open failed 
	{
	    throw FileNotFoundError(MolFile.c_str());
	}


// read and compute line strengths
    
    i = 0;
  
// initialize index_J_Kp_Km[maxJ][maxJ][maxJ] to -1

    for (int iv = 0; iv<maxJ; iv++)
	{
	    for (int ij = 0; ij<maxJ; ij++)
		{
		    for (int ikp = 0; ikp<maxJ; ikp++)
			{
			    for (int ikm=0; ikm<maxJ; ikm++)
				{
//				    cout << iv << " " ij << " " << ij2 << " " << ip << " " << index_v_J_K_p[iv][ij][ij2][ip] << endl;
				    
				    index_J_Kp_Km[ij][ikp][ikm] = -1;
				}
			}
		}
	}


  
// now read in the molecular data
    Jmax = 0;
    cout << "Reading molecular data...";
    float e_h213co, e_h2c18o; 
    do {
	inMolFile >> J_Of_Level[i] >> Kp_Of_Level[i] >> Km_Of_Level[i] 
		  >> Energy_Of_Level[i] >> e_h213co >> e_h2c18o;  // energies of h213co and h2c18o not used now
/*
	cout << i << " " << J_Of_Level[i] << " "  << Kp_Of_Level[i] << " "  << Km_Of_Level[i]  << " " 
	     << Energy_Of_Level[i]  << " " << e_h213co  << " " << e_h2c18o  << " " << endl;
*/
	g_Of_Level[i] = 2*J_Of_Level[i]+1;
	index_J_Kp_Km[ J_Of_Level[i] ][ Kp_Of_Level[i] ][ Km_Of_Level[i] ] = i;
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

    cout << "Reading molecular line strengths...";

    double sif;
    int Ji, Kpi, Kmi, Jf, Kpf, Kmf;

    do {
	inSifFile >> Ji >> Kpi >> Kmi >> Jf >> Kpf >> Kmf >> sif;
//	cout << Ji << " " << Kpi << " " << Kmi << " " << Jf << " "<< " "<< Kpf << " " << Kmf << " " << sif << endl;
	    // get the indices - using v=0
	sif *=1e-36;
	int index_i = index_J_Kp_Km[Ji][Kpi][Kmi];
	int index_f = index_J_Kp_Km[Jf][Kpf][Kmf];
#ifdef BLITZ
	S_if(index_i,index_f) = sif;
#else	
	S_if[index_i][index_f] = sif;
#endif
//	cout << index_i << " " << index_f << " " << sif << " " << size << endl;
	
    } while (!inSifFile.eof());
    
    cout << "finished!" << endl;

    cout << "Calculating Einstein Coefficients...";
    
    // calculate Einstein-Coefficients
    for (i=0; i<Number_Of_Levels; i++)
	{
	    for (f=0; f<i; f++)
		{
		    int Ji  = J_Of_Level[i];
		    int Jf  = J_Of_Level[f];
		    int Kpi = Kp_Of_Level[i];
		    int Kpf = Kp_Of_Level[f];
		    int Kmi = Km_Of_Level[i];
		    int Kmf = Km_Of_Level[f];
		    double gu  = g_Of_Level[i];
		    double ei = Energy_Of_Level[i];   // in cm-1
		    double ef = Energy_Of_Level[f];   // in cm-1

		    double freq = (ei-ef) * c_Light; // in Hz
#ifdef BLITZ
		    Frequency(i,f) = freq;
#else
		    Frequency[i][f] = freq;
#endif
		    
		    int deltaJ = Ji-Jf;

		    
#ifdef BLITZ
                    sif = S_if(i,f);
#else
                    sif = S_if[i][f];
#endif
		    if (i != f) 
			{
#ifdef BLITZ
			    Einstein_A(i,f) 
#else
				Einstein_A[i][f]  
#endif
				= 64 * pow(Pi,4) * pow(freq,3)/  (3*h_Planck*pow(c_Light, 3))*sif/gu;//this->Mu(0)*this->Mu(0)*sif;
#ifdef BLITZ
//			    cout << i << " " << f <<  " freq: " << freq << " sif: " << sif << " A: " << Einstein_A(i,f) << endl;
#else
//			    cout << i << " " << f << " freq: " << freq << " sif: " << sif << "A: " << Einstein_A[i][f] << endl;
#endif
			}
		    else 
			{
#ifdef BLITZ
			    Einstein_A(i,f) 
#else
				Einstein_A[i][f]  
#endif
				= 0;
			}
		    
			    
		    // induced emission

		    if (i != f && freq > 0) 
			{
#ifdef BLITZ
			    Einstein_B(i,f) = Einstein_A(i,f)
				* c_Light*c_Light/(2*h_Planck*freq*freq*freq);
#else
			    Einstein_B[i][f] = Einstein_A[i][f]
				* c_Light*c_Light/(2*h_Planck*freq*freq*freq);
#endif
			}
		    else 
			{
#ifdef BLITZ
			    Einstein_B(i,f) = 0;
#else
			    Einstein_B[i][f] = 0;
#endif
			}
		    
#ifdef BLITZ
//		    if (Einstein_A(i,f) != 0) 
//			{			    
//			    cout << i << " " << f << " " << freq << " " << Einstein_A(i,f) << " " << Einstein_B(i,f) << " " << sif <<endl;
//			}
#else
		    if (Einstein_A[i][f] != 0) 
			{
//			    cout << i << " " << f << " " << freq << " " << Einstein_A[i][f] << " " << Einstein_B[i][f] << " " << sif <<endl;
		}
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
    cout << "...finished!" << endl;
    
    cout << "Reading collision rates...";
    do
	{
	    // read Ji and Jf 
	    inColFile >> Ji >> Kpi >> Kmi >> Jf >> Kpf >> Kmf;
//	    cout << Ji << " " << Kpi << " " << Kpf << " " <<  Jf << " "  << Kpf << " " << Kmf << " "; //<< endl;
	    // get the indices - using v=0
	    int index_i = index_J_Kp_Km[Ji][Kpi][Kmi];
	    int index_f = index_J_Kp_Km[Jf][Kpf][Kmf];
//	    cout << index_i << " " << index_f << " " << Number_Of_Levels << endl;
	    // read the whole thing in
	    if (Ji <= Jmax && Jf <= Jmax && index_i >= 0 && index_f >= 0 ) 
		{
		    for (i=0; i<N_temp; i++)
			{
//			    cout << i << " " << index_i << " " << index_f << " in 1" << endl;
#ifdef BLITZ
			    inColFile >> CollRates(index_i,index_f,i);
//			    cout << CollRates(index_i,index_f,i) << " ";
#else
			    inColFile >> CollRates[index_i][index_f][i];
//			    cout << CollRates[index_i][index_f][i] << " ";
#endif
			}
#ifdef BLITZ
//		    cout << index_i << " " << index_f << " " << CollRates(index_i, index_f, 0) << endl;
#else
//		    cout << index_i << " " << index_f << " " << CollRates[index_i][index_f][0] << " " <<   CollRates[index_f][index_i][0] << endl;
#endif
		    
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
//			 << "tau(back)[1-0] T_l(back)[1-0] tau(HII)[1-0] T_l(HII)[1-0] tau(1-0) T_l(1-0) "
//			 << "tau(back)[2-1] etc." << endl;
		         << " tau(1) T_l(1)  tau(2) T_l(2) etc." << endl;
	    }
    
//    cout << Einstein_A << endl;
//    cout << Einstein_B << endl;
//    cout << CollRates(Range::all(),Range::all(),1) << endl;
   
}


AsymmetricRotor::~AsymmetricRotor() 
{
    delete [] Energy_Of_Level;
    delete [] J_Of_Level;
    delete [] Kp_Of_Level;
    delete [] Km_Of_Level;
    delete [] g_Of_Level;
    delete [] n_Of_Level;
}



int AsymmetricRotor::Kp(int index)
{
    if (index < 0 || index > NumberOfLevels()) throw VectorRangeError(index);
    return Kp_Of_Level[index];
}


int AsymmetricRotor::Km(int index)
{
    if (index < 0 || index > NumberOfLevels()) throw VectorRangeError(index);
    return Km_Of_Level[index];
}


double AsymmetricRotor::Sif(int i, int j)
{
#ifdef BLITZ
    return S_if(i,j);
#else
    return S_if[i][j];
#endif
}




