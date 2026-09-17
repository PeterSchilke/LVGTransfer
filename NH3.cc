//
// NH3.cc	-- Peter Schilke Wed Feb 12 1997
//
//  Time-stamp: <2005-12-29 18:34:31 schilke> 
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Mols.h"
//LinearVib
NH3::NH3(int size, string MolFile, string ColFile,
		     string OutFile, string PlotFile, double *dipole, double R_c)
{
    Rc = R_c;
    Number_Of_Levels = size;  size++;
    Energy_Of_Level = new double[size];
    v_Of_Level      = new int[size];
    J_Of_Level      = new int[size];
    K_Of_Level      = new int[size];
    p_Of_Level      = new int[size];
    g_Of_Level      = new double[size];
    n_Of_Level      = new double[size];
    b_Of_Level      = new double[size];
#ifdef BLITZ
    Frequency.resize(size,size);
    Einstein_A.resize(size,size);
    Einstein_B.resize(size,size);
    P.resize(size,size);
#endif
    int i, f;
    for (i = 0; i < maxVib*(maxVib+1)/2; i++)
	{
	    mu[i] = dipole[i];
	}
    ifstream inMolFile (MolFile.c_str(), ios::in);
    if (! inMolFile)  // open failed 
	{
	    throw FileNotFoundError(MolFile.c_str());
	}
    
    i = 0;
  
// initialize index_v_J_K_p[maxVib][maxJ][maxJ][maxP] to -1

    for (int iv = 0; iv<maxVib; iv++)
	{
	    for (int ij = 0; ij<maxJ; ij++)
		{
		    for (int ij2 = 0; ij2<maxJ; ij2++)
			{
			    for (int ip=0; ip<maxP; ip++)
				{
//				    cout << iv << " " ij << " " << ij2 << " " << ip << " " << index_v_J_K_p[iv][ij][ij2][ip] << endl;
				    
				    index_v_J_K_p[iv][ij][ij2][ip] = -1;
				}
			}
		}
	}


  
// now read in the molecular data
    Jmax = 0;
    cout << "Reading molecular data...";
    do {
	inMolFile >> v_Of_Level[i] >> J_Of_Level[i] >> K_Of_Level[i] >> p_Of_Level[i] 
		  >> Energy_Of_Level[i];
	g_Of_Level[i] = 2*J_Of_Level[i]+1;
	index_v_J_K_p[ v_Of_Level[i] ][ J_Of_Level[i] ][ K_Of_Level[i] ][ p_Of_Level[i] ] = i;
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
		    int vi = v_Of_Level[i];
		    int vf = v_Of_Level[f];
		    int Ji = J_Of_Level[i];
		    int Jf = J_Of_Level[f];
		    int Ki = K_Of_Level[i];
		    int Kf = K_Of_Level[f];
		    int pi = p_Of_Level[i];
		    int pf = p_Of_Level[f];
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
		    int deltaJ = Ji-Jf;
		    int deltaK = Ki-Kf;
		    double Mu;
		    
		    if (vi == vf)
			{
			    Mu =  (vi == 0) ? 1.47147 + 1.809e-4 * Ji*(Ji+1) - 3.467e-4*Ki*Ki :
				1.248 + 4.14e-4*Ji*(Ji+1) - 7.05e-4*Ki*Ki;
			}
		    else
			{
			    Mu = 0.23;
			}
		    Mu *= 1e-18;
			    
#ifdef BLITZ
		    Einstein_A(i,f) 
#else
                    Einstein_A[i][f]  
#endif
			= 64 * pow(Pi,4) * pow(freq,3)/
					  (3*h_Planck*pow(c_Light, 3))*Mu*Mu;
				    // Hoenl-London factors
		    if (deltaJ == 1 && deltaK == 0 && pi != pf)
			{
#ifdef BLITZ
			    Einstein_A(i,f) 
#else
                            Einstein_A[i][f] 
#endif
				*= (Ji*Ji-Ki*Ki)/(Ji*(2.*Ji+1.));
//					     cout << i << " " << Ji << ": " << Einstein_A(i,f) << endl;
			}
		    else if (deltaJ == 0 && deltaK == 0 && pi != pf) 
			{
#ifdef BLITZ					    
			    Einstein_A(i,f) 
#else
			     Einstein_A[i][f] 
#endif
				*= Ki*Ki/(Ji*(Ji+1.));
			}
		    else if (deltaJ == -1 && deltaK == 0 && pi != pf) 
			{
#ifdef BLITZ					    
			    Einstein_A(i,f) 
#else
			    Einstein_A[i][f] 
#endif
				*= ( (Ji+1)*(Ji+1)-Ki*Ki )/((Ji+1)*(2*Ji+1.));
			}
		    else // no deltaJ=-1 within a state
			{
#ifdef BLITZ
			    Einstein_A(i,f)
#else
			    Einstein_A[i][f]
#endif  
				*= 0;
			}
		    // induced emission
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
    int Ji, Jf, Ki, Kf, pi, pf;
    int index_i, index_f;
    cout << "Reading collision rates...";
    do
	{
	    // read Ji and Jf 
	    inColFile >> Ji >> Ki >> pi >> Jf >> Kf >> pf;
//	    cout << Ji << " " << Jf << " ";
	    // get the indices - using v=0
	    index_i = index_v_J_K_p[0][Ji][Ki][pi];
	    index_f = index_v_J_K_p[0][Jf][Kf][pf];
//	    cout << index_i << " " << index_f << " " << Number_Of_Levels << endl;
	    // read the whole thing in
	    if (Ji <= Jmax && Jf <= Jmax && index_i != index_f && index_i >= 0 && index_f >= 0 ) 
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


NH3::~NH3() 
{
    delete [] Energy_Of_Level;
    delete [] v_Of_Level;
    delete [] J_Of_Level;
    delete [] K_Of_Level;
    delete [] p_Of_Level;
    delete [] g_Of_Level;
    delete [] n_Of_Level;
}



int NH3::v(int index)
{
    if (index < 0 || index > NumberOfLevels()) throw VectorRangeError(index);
    return v_Of_Level[index];
}

int NH3::K(int index)
{
    if (index < 0 || index > NumberOfLevels()) throw VectorRangeError(index);
    return K_Of_Level[index];
}

int NH3::p(int index)
{
    if (index < 0 || index > NumberOfLevels()) throw VectorRangeError(index);
    return p_Of_Level[index];
}





