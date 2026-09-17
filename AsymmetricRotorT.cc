//
// Nh3.cc	-- Peter Schilke Wed Feb 12 1997
//
//  Time-stamp: <2008-02-13 12:54:18 schilke> 
//

#include <iostream>
#include <fstream>
#include <string>
#include "Mols.h"

//torsionally excited asymmetric rotor (e.g. Methanol)

AsymmetricRotorT::AsymmetricRotorT(int size, string MolFile, string ColFile,
		     string OutFile, string PlotFile, string SifFile,  double *dipole,double R_c)
{
    Rc = R_c;
    Number_Of_Levels = size;  size++;
    Energy_Of_Level = new double[size];
    J_Of_Level      = new int[size];
    K_Of_Level      = new int[size];
    vt_Of_Level     = new int[size];
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
    
  
// initialize index_J_K_vt[maxJ][maxJ][maxJ] to -1

    for (int iv = 0; iv<maxJ; iv++)
	{
	    for (int ij = 0; ij<maxJ; ij++)
		{
		    for (int ik = 0; ik<maxJ; ik++)
			{
			    for (int ivt=0; ivt<maxJ; ivt++)
				{
//				    cout << iv << " " ij << " " << ij2 << " " << ip << " " << index_v_J_K_p[iv][ij][ij2][ip] << endl;
				    
				    index_J_K_vt[ij][ik][ivt][0] = -1;
				    index_J_K_vt[ij][ik][ivt][1] = -1;
				}
			}
		}
	}


  
// now read in the molecular data
    Jmax = 0;
    cout << "Reading molecular data...";
    i = 0;
    do {
	inMolFile >> J_Of_Level[i] >> K_Of_Level[i] >> vt_Of_Level[i] 
		  >> Energy_Of_Level[i];  //
//	cout << i << ": " << J_Of_Level[i] << " " << K_Of_Level[i] << " " <<  vt_Of_Level[i] 
//	     << " " << Energy_Of_Level[i];  //
	g_Of_Level[i] = 2*J_Of_Level[i]+1;
	if (K_Of_Level[i] < 0) 
	    {
		index_J_K_vt[ J_Of_Level[i] ][ -K_Of_Level[i] ][ vt_Of_Level[i] ] [0] = i;
//		cout << " negative: " << i << endl;
	    }
	else
	    {
		index_J_K_vt[ J_Of_Level[i] ][ K_Of_Level[i] ][ vt_Of_Level[i] ] [1] = i;
//		cout << " positive: " << i << endl;
	    }
	
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

    cout << "Reading molecular line strenghts...";

    double sif;
    int Ji, Ki, vti, Jf, Kf, vtf;

    do {
	inSifFile >> vti >> Ji >> Ki >> vtf >> Jf >> Kf >> sif;
	    // get the indices - using v=0
	int index_i, index_f;
	if (Ki < 0) 
	    {
		index_i = index_J_K_vt[Ji][-Ki][vti][0];
	    }
	else
	    {
		index_i = index_J_K_vt[Ji][Ki][vti][1];
	    }
	if (Kf < 0) 
	    {
		index_f = index_J_K_vt[Jf][-Kf][vtf][0];
	    }
	else
	    {
		index_f = index_J_K_vt[Jf][Kf][vtf][1]; 
	    }
/*	if (Ji <= Jmax && Jf <= Jmax && index_i >= 0 && index_f >= 0 ) 
	    {
		cout  << Ji << " " << Ki << " " << vti << " " << Jf << " "<< " "<< Kf << " " << vtf 
		      << " " << index_i << " " << index_f  << " " << sif << endl;
	    }
*/
	sif *=1e-36;  // in Debye
	
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
		    int Ki  = K_Of_Level[i];
		    int Kf  = K_Of_Level[f];
		    int vti = vt_Of_Level[i];
		    int vtf = vt_Of_Level[f];
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
				= 64 * pow(Pi,4) * pow(freq,3)/  (3*h_Planck*pow(c_Light, 3))*sif/gu; //this->Mu(0)*this->Mu(0)*sif;

// well...
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

		    if (i != f) 
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
		    if (Einstein_A[i][f] == 0 && Einstein_B[i][f] != 0) 
			{
//			    cout << i << " " << f << " " << freq << " " << Einstein_A[i][f] 
//				 << " " << Einstein_B[i][f] << " " << sif <<endl;
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
    cout << " finished!" << endl;
    
    cout << "Reading collision rates...";
    do
	{
	    // read Ji and Jf 
	    inColFile >> Ji >> Ki >> vti >> Jf >> Kf >> vtf;
	    // get the indices - using v=0
	int index_i, index_f;
	if (Ki < 0) 
	    {
		index_i = index_J_K_vt[Ji][-Ki][vti][0];
	    }
	else
	    {
		index_i = index_J_K_vt[Ji][Ki][vti][1];
	    }
	if (Kf < 0) 
	    {
		index_f = index_J_K_vt[Jf][-Kf][vtf][0];
	    }
	else
	    {
		index_f = index_J_K_vt[Jf][Kf][vtf][1];
	    }
	
	    // read the whole thing in
//	cout << Ji << " " << Ki << ": " << index_i << " " << Jf << " " << Kf << ": " << index_f << endl;
	
	double rate;
	    if (Ji <= Jmax && Jf <= Jmax && index_i >= 0 && index_f >= 0 ) 
		{
//		    cout << Ji << " " << Ki << " " << vtf << " " <<  Jf << " "  << Kf << " " << vtf << " " 
//			 << index_i << " " << index_f << " "; //<< endl;
		    for (i=0; i<N_temp; i++)
			{
			    inColFile >> rate ;
//			    cout << rate << endl;
//			    cout << i << " " << index_i << " " << index_f << " in 1" << endl;
#ifdef BLITZ
			    CollRates(index_i,index_f,i) = rate;
//			    cout << CollRates(index_i,index_f,i) << " ";
#else
			    CollRates[index_i][index_f][i] = rate;
//			    cout << CollRates[index_i][index_f][i] << " ";
#endif
			}
//		    cout << endl;
		    
#ifdef BLITZ
//		    cout << index_i << " " << index_f << " " << CollRates(index_i, index_f, 0) << endl;
#else
//		    cout << index_i << " " << index_f << " " << CollRates[index_i][index_f][0] << endl;
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
//		    cout << "Problem - data ignored" << endl;
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


AsymmetricRotorT::~AsymmetricRotorT() 
{
    delete [] Energy_Of_Level;
    delete [] J_Of_Level;
    delete [] K_Of_Level;
    delete [] vt_Of_Level;
    delete [] g_Of_Level;
    delete [] n_Of_Level;
}



int AsymmetricRotorT::K(int index)
{
    if (index < 0 || index > NumberOfLevels()) throw VectorRangeError(index);
    return K_Of_Level[index];
}


int AsymmetricRotorT::vt(int index)
{
    if (index < 0 || index > NumberOfLevels()) throw VectorRangeError(index);
    return vt_Of_Level[index];
}


double AsymmetricRotorT::Sif(int i, int j)
{
#ifdef BLITZ
    return S_if(i,j);
#else
    return S_if[i][j];
#endif
}




