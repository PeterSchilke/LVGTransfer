//
// J.cc	-- Peter Schilke Wed Jun 25 1997
//
//  Time-stamp: <2008-02-13 13:10:47 schilke> 
//
#include "Mols.h"

double Transitions::calcJ(int i, int f, Cloud &thisCloud)  // Radiation field
{
//    cout << "in calcJ" << endl;
    int I = (i>f) ? i : f; int F = (i>f) ? f : i;  // make I > F
    double J = 0;
    double freq = this->frequency(I,F); 
    double wave = c_Light/freq * 1e4;   // wavelength in mic
    
        
    if (freq == 0) return J;
// continuum radiation field
    double B_d = B_Planck(thisCloud.Tdust(), freq); // dust radiation field
    double B_back = B_Planck(thisCloud.Tback(), freq);  // background radiation field
    double tauBack = thisCloud.tau100mic() * pow(wave/100, -thisCloud.beta_back());
    double I_back = B_back * (1 - exp(-tauBack));
    double Wback = thisCloud.Wback();
    double I_cosmic = B_Planck(thisCloud.T_cosmic(), freq);
    double T_e = thisCloud.Te();
    double tauHII = 8.235e-2 * pow(T_e,-1.35) * pow(freq*1.e-9,-2.1) * thisCloud.EM();
    double S_HII = B_Planck(T_e, freq) * (1 - exp(-tauHII));
    double WHII = thisCloud.WHII();
    
//    cout << thisCloud.Tback() << " " << tauBack << " " << freq << " " << wave << endl;
//    cout << thisCloud.Te() << " " << tauHII << " " << thisCloud.EM() << " " << S_HII << endl;
    

    double I_inf = I_back * Wback + S_HII * WHII + I_cosmic;  // background radiation field
//    cout << "I_inf: " << I_inf << " S_HII: " << S_HII << " WHII: " << WHII << " I_cosmic: " << I_cosmic << endl;
//    cout << "freq: " << freq << " wave: " << wave << endl;
    

//    double I_inf =  I_cosmic;  // background radiation field
// molecular parameters
//    cout << "calcJ: i f " << i << " " << f << endl;
    double nsum = 0;
    for (i=0; i< Number_Of_Levels; i++) 
	{
	    nsum += n_Of_Level[i]*b_Of_Level[i];
	}
    
    
    double A = this->A(I,F);  // Einstein-A coefficient
    double N_tot = thisCloud.Nmol() * 1e5/V_conv;
    double n0 = N_tot/nsum;
    double ni = n_Of_Level[I]*b_Of_Level[I];
    double nf = n_Of_Level[F]*b_Of_Level[F];

    if (A == 0. || ni == 0. || nf == 0.) {
//	cout << "I_inf:" << I_inf << " " << freq << endl;
	return I_inf;
    }
    
// no transition or no levels -> no contribution from line
    
    double gi = g_Of_Level[I];
    double gf = g_Of_Level[F];
    int Ji = J_Of_Level[I];
    int Jf = J_Of_Level[F];

    //cout << "calcJ: all parameters set" << endl;
    

    double R  = nf/ni * gi/gf;
    double delta_f = freq/c_Light * thisCloud.delta_v()*1e5; 
// molecular absorption coefficient    
    double kap_m_0 = A * c_Light*c_Light/(8*Pi*freq*freq); 
    double kap_m = kap_m_0 * ni * n0 * (R-1.);
// molecular emission coefficient    
   double eps_m  = h_Planck*freq/(4*Pi) * A * ni * n0;
// molecular optical depth   
   double  tau_m = kap_m * c_Light/(freq * thisCloud.delta_v()*1e5);
   
// dealing with maser emission    
  if (tau_m < -10) tau_m = -10.;
  
// now dust absorption
  double kap_d, eps_d, tau_d_inf, tau_d_ds;
  
  if (thisCloud.length() > 0) {   
// dust absorption coefficient 
      kap_d =  kappaCalc(freq,thisCloud.nH2());
// dust emission coefficient 
      eps_d = kap_d * B_d;
// dust total optical depth
      tau_d_inf = thisCloud.length() * kap_d;
// dust linewidth optical depth
      double delta_v_0 = 15000;
      // multiplied with sqrt(T) gives width
      tau_d_ds = delta_v_0 *
	sqrt(thisCloud.Tkin())/thisCloud.vgrad() * kap_d;
  } else 
      {
	  kap_d = 0;
	  eps_d = 0;
	  tau_d_inf = 0;
	  tau_d_ds = 0;
      }
  
// total optical depth 
  double tau_plus = tau_m + tau_d_ds;

//  background intensity
  double J_1, J_2, J_3, beta_m, beta_plus, S_plus, S_m;

  if (this->MolName() == "dcn_hfs") 
      {
	  double tauint_1[] = {0.333, 0.556, 0.111};
	  double tauint_2[] = {0.083, 0.111, 0.006, 0.467, 0.083, 0.250};
	  if (Ji == 1 && Jf == 0) 
	      {
//		  cout << "DCN 1-0 hfs correction applied\n";
		  beta_m = beta_plus = 0;
		  double tau_hfs, weight;
		  for (int index=0;index<3;index++) {
//
// this assumes beta = sum int_hfs beta(hfs)
//
		      weight = tauint_1[index];
		      tau_hfs = tauint_1[index]*tau_m;
		      beta_m += weight * (1. - exp(-tau_hfs))/tau_hfs;
		      beta_plus +=  weight * (1. - exp(-(tau_hfs+tau_d_ds)))/
			  (tau_hfs+tau_d_ds);
		  }
	      }
	  else if (Ji == 2 && Jf == 1)
	      {
//		  cout << "DCN 2-1 hfs correction applied\n";
		  beta_m = beta_plus = 0;
		  double tau_hfs, weight;
		  for (int index=0;index<6;index++) {
		      tau_hfs = tauint_2[index]*tau_m;
		      weight = tauint_2[index];
		      beta_m += weight* (1. - exp(-tau_hfs))/tau_hfs;
		      beta_plus += weight* (1. - exp(-(tau_hfs+tau_d_ds)))/
			  (tau_hfs+tau_d_ds);
		  }
	      }
	  else 
	      {
		  if (fabs(tau_m) > 1.e-5) 
		      {   //
			  beta_m = (1. - exp(-tau_m))/tau_m;
		      }
		  else
		      {
			  beta_m = 1. - tau_m/2.;
		      }
		  if (fabs(tau_plus) > 1.e-5) 
		      {   //
			  beta_plus = (1. - exp(-tau_plus))/tau_plus;
		      }
		  else
		      {
			  beta_plus = 1. - tau_plus/2.;
		      }

	      }
	  
      } else {

	      if (fabs(tau_m) > 1.e-5) 
		  {   //
		      beta_m = (1. - exp(-tau_m))/tau_m;
		  }
	      else
		  {
		      beta_m = 1. - tau_m/2.;
		  }
	      if (fabs(tau_plus) > 1.e-5) 
		  {   //
		      beta_plus = (1. - exp(-tau_plus))/tau_plus;
		  }
	      else
		  {
		      beta_plus = 1. - tau_plus/2.;
		  }
	  }
//  cout << Ji << " - " << Jf << " beta_m " << beta_m << endl;
  
  S_plus = (eps_m + eps_d)/(kap_m + kap_d);
  S_m = eps_m/kap_m;
//    total integrated intensities
  J_1 = I_inf * exp(-tau_d_inf) * beta_m;
  J_2 = S_plus * (1. - beta_plus);
  J_3 = B_d * (beta_plus - beta_m * exp(-tau_d_inf));

  J = J_1 + J_2 + J_3;

/*
  cout << endl << "i: " << I << " f: " << F << " S: "<< S_plus << " tau: " << tau_m << " beta: " << beta_m << endl;
  cout << endl << Ji << " "  << Jf << " " << J << " " << J_1 << " " << J_2 << " " << J_3 << endl;
  cout << "S: " << S_plus << " " << S_m << endl;
  cout << "tau: " << tau_plus << " "  << tau_m << endl;
  cout << "beta: " << beta_m << " "  << beta_plus << endl;
  cout << "dust: " << tau_d_inf << " " << kap_d << endl;
*/

  return J;
}
