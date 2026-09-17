//
// MinMaxInput.cc	-- Peter Schilke Mon Sep  1 1997
//
//  Time-stamp: <2006-01-03 17:43:14 schilke> 
//
#include "Mols.h"

void MinMaxInput_Xmol(double& TkinMin,double& TkinStep,double& TkinMax,
		 double& nH2Min,double& nH2Fac,double& nH2Max,
		 double& XeMin, double& XeFac, double& XeMax, double& X_mol,
		 double& Tdust,double& NH2,double& delta_v,
		 double& Tback,double& beta_back, double& tau100mic, double& Wback,
		 double& Te,double& EM, double& WHII, double& T_cosmic)
{
    
    cout << endl;
    TkinMin = read("TkinMin ");
    TkinStep = read0("\tTkinStep ");
    TkinMax = read("\t\tTkinMax ");

    cout << endl;
    nH2Min = read("nH2Min ");
    nH2Fac = read("\tnH2Fac ");
    if (nH2Fac < 0) 
	{
	    nH2Fac *= -1;
	    nH2Fac = 1./pow(2., nH2Fac);
	    nH2Fac = pow(10,nH2Fac);
	}
    nH2Max = read("\t\tnH2Max ");

    cout << endl;
    XeMin = read("XeMin ");
    XeFac = read("\tXeFac ");
    if (XeFac < 0) 
	{
	    XeFac *= -1;
	    XeFac = 1./pow(2., XeFac);
	    XeFac = pow(10,XeFac);
	}
    XeMax = read("\t\tXeMax ");

    cout << endl;
    X_mol = read("X_mol ");

    cout << endl;
    Tdust = read("T_dust");
    NH2   = read0("N(H_2)");
    delta_v = read("delta_v");
    Tback = read("Tback");
    beta_back = read0("beta_back");
    tau100mic = read0("tau100mic");
    Wback = read0("Wback");
    Te = read("Te");
    EM = read0("EM");
    WHII = read0("WHII");
    T_cosmic = read0("T_cosmic");
}
