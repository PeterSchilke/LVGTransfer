//
// PrintOut.cc	-- Peter Schilke Tue Mar  4 1997
//
//  Time-stamp: <2007-12-17 11:18:27 schilke> 
//
#include <iostream>
#include <iomanip>
#include "Mols.h"
#include "extra.h"

void SymmetricRotor::PrintOut(Cloud &thisCloud) 
{
    cout << "not yet implemented" << endl;
}

void NH3::PrintOut(Cloud &thisCloud)
{
    int i, f;
    
// header
    
    double N_tot = thisCloud.Nmol() * 1e5/V_conv;
    
    cout << endl << " The calculation for "
	 << BOLD << this->MolName() << OFF << " used "
	 << BOLD << Number_Of_Levels << OFF << " levels" << endl;
    cout << endl;
    
    cout << " T_kin  = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.Tkin();
    cout << "    n(H_2) = ";
    cout.setf(ios::scientific, ios::floatfield);
    cout << setw(10) << setprecision(6) << thisCloud.nH2();
    cout << "    N(Mol) = ";
    cout.setf(ios::scientific, ios::floatfield);
    cout << setw(10) << setprecision(6) << N_tot;
    cout << endl;

    cout << " T_dust = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.Tdust();
    cout << "    N(H_2) = ";
    cout.setf(ios::scientific, ios::floatfield);
    cout << setw(10) << setprecision(6) << thisCloud.NH2();
    cout << "    delta_v = ";
    cout.setf(ios::scientific, ios::floatfield);
    cout << setw(10) << setprecision(6) << thisCloud.delta_v();
    cout << endl;
 
    cout << " T_back = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.Tback();
    cout << "    beta_back = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.beta_back();
    cout << "       tau100mic = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.tau100mic();
    cout << "    Wback = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.Wback();
    cout << endl;
 
 
    cout << " T_e = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.Te();
    cout << "     EM = ";
    cout.setf(ios::scientific, ios::floatfield);
    cout << setw(10) << setprecision(6) << thisCloud.EM();
    cout << "  WHII = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(8) << setprecision(4) << thisCloud.WHII();
    cout << endl;
 
    cout << " T_cosmic = ";
    cout.setf(ios::fixed, ios::floatfield);
    cout << setw(6) << setprecision(2) << thisCloud.T_cosmic();
    cout << endl << endl;

   cout << " vi Ji Ki pi vf Jf Kf pf    T_ex        freq    tau(Back)    T_l(Back)     tau(HII)     T_l(HII)        T_bg          tau         T_l"  
	 << endl;

    outFile << endl << " The calculation for "
	 << BOLD << this->MolName() << OFF << " used "
	 << BOLD << Number_Of_Levels << OFF << " levels" << endl;
    outFile << endl;
    
    outFile << " T_kin  = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.Tkin();
    outFile << "    n(H_2) = ";
    outFile.setf(ios::scientific, ios::floatfield);
    outFile << setw(10) << setprecision(6) << thisCloud.nH2();
    outFile << "    N(Mol) = ";
    outFile.setf(ios::scientific, ios::floatfield);
    outFile << setw(10) << setprecision(6) << N_tot;
    outFile << endl;

    outFile << " T_dust = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.Tdust();
    outFile << "    N(H_2) = ";
    outFile.setf(ios::scientific, ios::floatfield);
    outFile << setw(10) << setprecision(6) << thisCloud.NH2();
    outFile << "    delta_v = ";
    outFile.setf(ios::scientific, ios::floatfield);
    outFile << setw(10) << setprecision(6) << thisCloud.delta_v();
    outFile << endl;
 
    outFile << " T_back = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.Tback();
    outFile << "    beta_back";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.beta_back();
    outFile << "    tau100mic = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.tau100mic();
    outFile << "    Wback = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.Wback();
    outFile << endl;

    outFile << " T_e = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.Te();
    outFile << "    EM = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.EM();
    outFile << "    WHII = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(8) << setprecision(4) << thisCloud.WHII();
    outFile << endl;
 
    outFile << " T_cosmic = ";
    outFile.setf(ios::fixed, ios::floatfield);
    outFile << setw(6) << setprecision(2) << thisCloud.T_cosmic();
    outFile << endl << endl;
 
    outFile << " vi Ji Ki pi vf Jf Kf pf    T_ex        freq    tau(Back)    T_l(Back)     tau(HII)     T_l(HII)     T_bg             tau          T_l"	    << endl;



    if (Convergence == 1)
	// only write to .plt file if converged
	{
	    plotFile << thisCloud.Tkin() << " ";
	    plotFile << thisCloud.nH2() << " ";
	    plotFile << N_tot << " ";
	    plotFile << thisCloud.Tback() << " ";
	    plotFile << thisCloud.tau100mic() << " ";
	    plotFile << thisCloud.Wback() << " ";
	    plotFile << thisCloud.Te() << " ";
	    plotFile << thisCloud.EM() << " ";
	    plotFile << thisCloud.WHII() << " ";
	}
    double nsum = 0;
    for (i=0; i< Number_Of_Levels; i++) 
	{
	    nsum += n_Of_Level[i]*b_Of_Level[i];
	}
    
    double n0 = N_tot/nsum; 
    
    for (i=1; i<Number_Of_Levels; i++){
	for (f=0; f<i; f++){
	    double ni = n_Of_Level[i]*b_Of_Level[i];
	    double nf = n_Of_Level[f]*b_Of_Level[f];
	    double gi = g_Of_Level[i];
	    double gf = g_Of_Level[f];
	    int vi = v_Of_Level[i];
	    int vf = v_Of_Level[f];
	    int Ji = J_Of_Level[i];
	    int Jf = J_Of_Level[f];
	    int Ki = K_Of_Level[i];
	    int Kf = K_Of_Level[f];
	    int pi = p_Of_Level[i];
	    int pf = p_Of_Level[f];
	    
	    double freq = this->frequency(i,f);
	    double A = this->A(i,f);  // Einstein-A coefficient

	    if (ni > 0. && nf > 0. && ni != nf && A != 0){
//		double R  = ni/nf * gf/gi;
		double R  = nf/ni * gi/gf;
		double T_ex = freq * GHzToK * 1e-9/log(R);
		double c = c_Light/freq;
		double wave = c_Light/freq * 1e4;   // wavelength in mic
		double tau_0 = A*c*c*c/(8*Pi*thisCloud.delta_v()*1e5);
		double tau = tau_0 * ni * n0 * (R-1.);
		if (tau < -100) tau = -100;
//		     dust absorption coefficient */
		double kap_d = kappaCalc(freq,thisCloud.nH2());
		    /* dust optical depth */
		double tau_d = thisCloud.delta_v()
		    * sqrt(thisCloud.Tkin())/thisCloud.vgrad() * kap_d;
		    /* total optical depth of dust */
                double tau_d_inf = thisCloud.length() * kap_d;
		double tauBack = thisCloud.tau100mic() * pow(wave/100, -thisCloud.beta_back());
		double Wback = thisCloud.Wback();
		double T_lBack = RJ(thisCloud.Tback(),freq)* (1 - exp(-tauBack)) * Wback;
		double T_e = thisCloud.Te();
		double tauHII = 8.235e-2 * pow(T_e,-1.35) * pow(freq*1.e-9,-2.1) * thisCloud.EM();
		double T_lHII = RJ(T_e, freq) * (1 - exp(-tauHII)) * thisCloud.WHII();
		double T_l = (RJ(T_ex,freq) - RJ(thisCloud.T_cosmic(),freq) - T_lBack -T_lHII
//			      - RJ(thisCloud.Tdust(),freq)*(1-exp(-tau_d_inf))
		    ) * (1. - exp(-tau));
		
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << vi;
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << Ji;
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << Ki;
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << pi;
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << vf;
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << Jf;
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << Kf;
		cout.setf(ios::fixed, ios::floatfield);
		cout << setw(3) << setprecision(0) << pf;
		cout.setf(ios::fixed, ios::floatfield);
		cout << "  " << setw(7) << setprecision(2) << T_ex;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(10) << setprecision(4) << freq*1e-9;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(11) << setprecision(4) << tauBack;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(11) << setprecision(4) <<  T_lBack;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(11) << setprecision(4) << tauHII;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(11) << setprecision(4) <<  T_lHII;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(10) << setprecision(4) << T_lBack+T_lHII;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(11) << setprecision(4) << tau;
		cout.setf(ios::scientific, ios::floatfield);
		cout << "  " << setw(10) << setprecision(4) << T_l;
		cout << endl;

		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setw(3) << setprecision(0) << Ji;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setw(3) << setprecision(0) << Ki;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setw(3) << setprecision(0) << pi;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setw(3) << setprecision(0) << Jf;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setw(3) << setprecision(0) << Kf;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setw(3) << setprecision(0) << pf;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << "  " << setw(7) << setprecision(2) << T_ex;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(10) << setprecision(4) << freq*1e-9;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(11) << setprecision(4) << tauBack;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(11) << setprecision(4) << T_lBack;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(11) << setprecision(4) << tauHII;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(11) << setprecision(4) << T_lHII;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(10) << setprecision(4) << T_lBack+T_lHII;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(11) << setprecision(4) << tau;
		outFile.setf(ios::scientific, ios::floatfield);
		outFile << "  " << setw(10) << setprecision(4) << T_l;
		outFile << endl;

		if (Convergence == 1)
		    // only write to .plt file if converged
		    {
			plotFile << tauBack << " ";
			plotFile << T_lBack << " ";
			plotFile << tauHII << " ";
			plotFile << T_lHII << " ";
			plotFile << T_ex  << " ";
			plotFile << tau << " ";
			plotFile << T_l << " ";
		    }
	    }
	}
    }
    outFile << endl << endl;
    

/*
    cout << endl << "n(i)  n(f)  n0  A(i,f)  B(i,f)  J(i,f)  C(i,f)  C(f,i) " << endl;
    for (i=0; i<Number_Of_Levels; i++){
	for (f=0; f<Number_Of_Levels; f++){
	    double n0 = N_tot/n_Of_Level[Number_Of_Levels];
	    cout << setiosflags(ios::fixed);
	    cout << setw(8) << i << ", " << f << ": ";    
	    cout.setf(ios::scientific, ios::floatfield);
	    cout << setw(10) << setprecision(3) << n_Of_Level[i] << " ";
	    cout << setw(10) << setprecision(3) << n_Of_Level[f] << " ";
	    cout << setw(10) << setprecision(3) << n0 << " ";
	    cout << setw(10) << setprecision(3) << Einstein_A[i][f] << " ";
	    cout << setw(10) << setprecision(3) << Einstein_B[i][f] << " ";
	    cout << setw(10) << setprecision(3) << Einstein_B[i][f]*this.calcJ(i,f,thisCloud) << " ";
	    cout << setw(10) << setprecision(3) << Collisions[i][f] << " ";
	    cout << setw(10) << setprecision(3) << Collisions[f][i] << " ";
	    cout << setw(10) << setprecision(3) << P[i][f] << " ";
	    cout << setw(10) << setprecision(3) << P[f][i] << endl;
	}
    }
    cout << "PrintOut" << endl;
    */

    for (int vi=0; vi<=1; vi++) 
	for(int vf=0; vf<=vi; vf++)
	    for(int ji=0; ji<=maxJ; ji++)
		for(int ki=0;ki<=ji;ki++)
		    for(int jf=0; jf<=ji; jf++)
			for(int kf=0;kf<=jf;kf++) {
			    string Mol = this->MolName();
//			    cout << Mol << endl;
			    if ( ( Mol == "nh3-o" ) && (ki != (ki/3)*3 || kf != (kf/3)*3)) 
								continue;
			    if ( ( Mol == "nh3-p" )  &&  (ki == (ki/3)*3 || kf == (kf/3)*3)) 
								continue;
			    if (fabs(float(ji-jf)) > 3 || ji > 10) continue;
			    if (!(ji == ki && jf == kf)) continue;
			    if (ji == jf && vi == vf) continue;
			    int i0 = index_v_J_K_p[vi][ji][ki][0]; 
			    int f0 = index_v_J_K_p[vf][jf][kf][0];
			    int i1 = index_v_J_K_p[vi][ji][ki][1]; 
			    int f1 = index_v_J_K_p[vf][jf][kf][1];
			    int index_i = (i0>i1) ? i0 : i1;
			    int index_f = (f0>f1) ? f0 : f1;
//			    cout << Number_Of_Levels << " " << index_i << " " << index_f << endl;
			    if (index_i >= Number_Of_Levels || index_f >= Number_Of_Levels) continue;
			    if (index_i < 0 || index_f < 0) continue;
			    double gi = g_Of_Level[index_i];
			    double gf = g_Of_Level[index_f];
			    double ni = n_Of_Level[index_i]*b_Of_Level[index_i];
			    double nf = n_Of_Level[index_f]*b_Of_Level[index_f];
			    double freq = this->frequency(index_i,index_f);
//			    cout << index_i << " " << index_f << " " << freq << " " << ni << " " << nf << endl;
			    
			    if (ni > 0. && nf > 0. &&
						(ni != nf || gi != gf)){
				double R = gf/gi*ni/nf;
				double T_rot;
				if (R != 0 && R != 1) 
				    T_rot = -freq * GHzToK * 1e-9/log(R);
				else T_rot = 0;
				if(vi == vf && T_rot != 0.0) {
				    printf("T_rot(%d)[%3d%3d%3d%3d]\t = %7.2f\n"
					    ,vi, ji, ki, jf, kf, T_rot);
				    outFile << "T_rot(";
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(1) << setprecision(0) << vi;
				    outFile << ") [";
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << ji;
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << ki;
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << jf;
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << kf;
				    outFile << "] = ";
				    outFile.setf(ios::fixed, ios::floatfield);
				    outFile << "  " << setw(10) << setprecision(4) << T_rot << endl;
				}
				else if (vi > vf && T_rot != 0.0) {
				    printf("T_vib [%3d%3d%3d%3d]\t = %7.2f\n",
						      ji, ki, jf, kf, T_rot);
				    outFile << "T_vib[";
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << ji;
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << ki;
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << jf;
				    outFile.setf(ios::scientific, ios::floatfield);
				    outFile << setw(3) << setprecision(0) << kf;
				    outFile << "] = ";
				    outFile.setf(ios::fixed, ios::floatfield);
				    outFile << "  " << setw(10) << setprecision(4) << T_rot << endl;
				}
				if (Convergence == 1)
				    {
					plotFile << T_rot << " ";
				    }
			    }
			}

    if (Convergence == 1)
	// only write to .plt file if converged
	{
	    plotFile << endl;
	}
    

}

