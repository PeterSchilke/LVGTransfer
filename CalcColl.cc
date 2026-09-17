//
// CalcColl.cc	-- Peter Schilke Tue Mar  4 1997
//
#include <iostream>
#include "Mols.h"


void Transitions::CalcColl(Cloud &thisCloud)
{
    int index=-1;
    for (int i=N_temp-1; i >= 0 ; i--) 
	{
	    if (this->T(i) <= thisCloud.Tkin()) 
		{
		    index = i;
		    break;
		}
	}
    // so Temperature is between index and index+1
    // now linear interpolation
    double factor;
    if (index == -1) // extrapolation to low temperatures
	{
	    factor = 0;
	    index++;
	}
    else if (index == N_temp-1) // extrapolation to high temperatures
	{
	    factor = 1;
	    index--;
	}
    else  // interpolation
	{
	    factor = (thisCloud.Tkin() - this->T(index))
		/(this->T(index+1) - this->T(index));
	}
//    cout << "CalcColl: index factor " << index << " " << factor << endl;
    for (int i=0; i < Number_Of_Levels; i++)
	{
	    for (int f=0; f < i; f++)
		{
		    double C_index      = this->Cr(i,f,index);
		    double C_index_plus = this->Cr(i,f,index+1);
		    double Ji = J_Of_Level[i];
		    double Jf = J_Of_Level[f];
		    double DeltaJ = Ji - Jf;
		    double gi = g_Of_Level[i];
		    double gf = g_Of_Level[f];
		    double Ei = Energy_Of_Level[i];  // in cm-1
		    double Ef = Energy_Of_Level[f];
		    double Delta_E = (Ei - Ef)*cmToK;  // in K
		    double Tkin = thisCloud.Tkin();
		    double Ra = 2*sqrt(Rc*1e-10/a0); // Rc in Angstrom 
		    double D = mu[0]*Dtonat;  // in Debye
//		    cout << "i f C " << i << " " << f << " " << C_index << endl;
		    
		    
#ifdef BLITZ
		    Collisions(i,f) = C_index + factor*(C_index_plus-C_index);
		    Collisions(f,i) = Collisions(i,f)
			* gi/gf * exp(-Delta_E/Tkin);
#else
		    Collisions[i][f] = C_index + factor*(C_index_plus-C_index);
		    Collisions[f][i] = Collisions[i][f]
			* gi/gf * exp(-Delta_E/Tkin);
#endif
//			    cout << Ji << " " << Jf << " " << Collisions[i][f] << " " <<  Collisions[f][i]  << endl;
// now collisions with electrons: formalism from Bhattacharyya,Bhattacharyya,Narayan 1981, ApJ, 247, 936 
		    double Long = 0;
		    double Close = 0;
// formalism from Dickinson & Flower 1981, MNRAS 196, 297
		    double Rate = 0;
		    if (DeltaJ == 1) 
			{
// BBN: my numbers are different, because they use a higher dipole moment
			    Long  = 7.194e-7/sqrt(Tkin) * D*D * Ji/(2*Ji+1) * exp(Delta_E/(2*Tkin))
				* ( 58.04*exp(-fabs(Delta_E)/(2*Tkin)) + 1.521e-3/sqrt(fabs(Delta_E*KToau)) 
				    * pow(Tkin,0.75)
				    -6.47e-9/fabs(Delta_E*KToau) * pow(Tkin,1.5) );
// contribution from close trajectories
			    double n = 5;  // n=5 for HCO+ ONLY!!!
			    double eta = Ji/(2*Ji+1)/n;
			    Close = 1.44e-6/sqrt(Tkin) *  eta
				* (Ra * (1+3*Ra) - 8/(1+Ra));
// DF
/*   not used now
			    Em = 3.1 * pow((Ei-Ef)/2/Ry, 0.6666667) * Ry * cmToK; // some Energy they use: here in K
			    double x = Em/Tkin;
			    double E1 = exp(-x) * log(1.+exp(-0.577/(1+2*x))/x);  // exponential integral
			    Rate = 3.45e-5 * Ji/(2*Ji+1)/sqrt(Tkin) * D*D * 
				(2*Pi/(3*sqrt(3)) + E1 + 0.95*x/pow(1+x/2,3));
*/
			}
		    else if (DeltaJ == 2)
			{
// BBN: DF don't have that
			    Long  = 0;  // no long range forces
			    double eta = 3*(Ji+1)*(Ji+2)/(2*(2*Ji+3)*(2*Ji+1));
// hope that's right: they don't give numbers. had to correct to get deexcitation rate
			    Close = 1.44e-6/sqrt(Tkin) *  eta * gf/gi
				* (Ra * (1+3*Ra) - 8/(1+Ra));
			}
		    else
			{
			    Long  = 0;
			    Close = 0;
			}
#ifdef BLITZ
		    if ( this->MolName() == "hco+" ) 
			{
			    Collisions_e(i,f) = Long + Close;
			    Collisions_e(f,i) = Collisions_e(i,f)
				* gi/gf * exp(-Delta_E/Tkin);
			}
		    else
			{
			    Collisions_e(i,f) = 0;
			    Collisions_e(f,i) = 0;
			}

#else
		    
		    if ( this->MolName() == "hco+")  
			{
			    Collisions_e[i][f] = Long + Close;
			    Collisions_e[f][i] = Collisions_e[i][f]
				* gi/gf * exp(-Delta_E/Tkin);
// Tennyson & Faure - not used
			    double a, b, c;
			    if (Ji == 0 && Jf == 1){
				a = 9.169e-6;
				b = -0.2479;
				c = 12.83;
			    } else if (Ji == 0 && Jf == 2) {
				a = 1.317e-6;
				b = -0.5198;
				c = 22.84;
			    } else if (Ji == 1 && Jf == 0) {
				a = 3.055e-6;
				b = -0.2478;
				c = 8.413;
			    } else if (Ji == 1 && Jf == 2) {
				a = 5.384e-6;
				b = -0.2421;
				c = 9.756;
			    } else if (Ji == 2 && Jf == 0) {
				a = 2.633e-7;
				b = -0.5196;
				c = 9.842;
			    } else if (Ji == 2 && Jf == 1) {
				a = 3.229e-6;
				b = -0.2420;
				c = 1.031;
			    } else {
				a = b = c = 0;
			    }
			    double erate = a * pow(Tkin/300,b) * exp(-c/Tkin);
//			    cout << Ji << " " << Jf << " " << Collisions_e[i][f] << " " <<  Collisions_e[f][i] << " " << erate << endl;
			}
		    else
			{
			    Collisions_e[i][f] = 0;
			    Collisions_e[i][f] = 0;
			}
#endif
/* just for debugging
		    double Longb = Long * gi/gf * exp(-Delta_E/Tkin);
		    double Closeb = Close * gi/gf * exp(-Delta_E/Tkin);
		    double Rateb = Rate * gi/gf * exp(-Delta_E/Tkin);
		    
		    cout << i << " " << f << " " << Delta_E << " " 
			 << Long*1e7 << " " << Longb*1e7 << " " << Close*1e7 << " " << Closeb*1e7 << " " << Rate*1e7 
			 << " " << Rateb*1e7 << endl;
*/
		}
	}
}

