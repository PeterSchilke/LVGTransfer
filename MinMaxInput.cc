//
// MinMaxInput.cc	-- Peter Schilke Mon Sep  1 1997
//
//  Time-stamp: <2007-11-14 18:45:05 schilke> 
//
#include "Mols.h"

void MinMaxInput(double& TkinMin,double& TkinStep,double& TkinMax,
		 double& nH2Min,double& nH2Fac,double& nH2Max,
		 double& XeMin, double& XeFac, double& XeMax,
		 double& NmolMin,double& NmolFac,double& NmolMax,
		 double& Tdust,double& NH2,double& delta_v,
		 double& TbackMin,double& TbackStep,double& TbackMax,
		 double& beta_back, 
		 double& tau100micMin,double& tau100micFac,double& tau100micMax, 
		 double& Wback,
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
    XeMin = read0("XeMin ");
    XeFac = read("\tXeFac ");
    if (XeFac < 0) 
	{
	    XeFac *= -1;
	    XeFac = 1./pow(2., XeFac);
	    XeFac = pow(10,XeFac);
	}
    XeMax = read0("\t\tXeMax ");

    cout << endl;
    NmolMin = read("NmolMin ");
    NmolFac = read("\tNmolFac ");
    if (NmolFac < 0) 
	{
	    NmolFac *= -1;
	    NmolFac = 1./pow(2., NmolFac);
	    NmolFac = pow(10,NmolFac);
	}
    NmolMax = read("\t\tNmolMax ");

    cout << endl;
    Tdust = read("T_dust");
    NH2   = read0("N(H_2)");
    delta_v = read("delta_v");
    TbackMin = read("TbackMin ");
    TbackStep = read0("\tTbackStep ");
    TbackMax = read("\t\tTbackMax ");

    cout << endl;

    beta_back = read0("beta_back");

    tau100micMin = read("tau100micMin ");
    tau100micFac = read("\ttau100micFac ");
    if (tau100micFac < 0) 
	{
	    tau100micFac *= -1;
	    tau100micFac = 1./pow(2., tau100micFac);
	    tau100micFac = pow(10,tau100micFac);
	}
    tau100micMax = read("\t\ttau100micMax ");

    cout << endl;
    
    Wback = read0("Wback");
    Te = read("Te");
    EM = read0("EM");
    WHII = read0("WHII");
    T_cosmic = read0("T_cosmic");
}
