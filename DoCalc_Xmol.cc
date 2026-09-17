//
// calculate.cc	-- Peter Schilke Fri Jun  5 1998
//
//  Time-stamp: <2006-01-03 18:05:05 schilke> 
//
#include <sstream>
#include <string>
#include "Mols.h"
#include "extra.h"

void Transitions::DoCalc_Xmol(Cloud &thisCloud,char sl,char *bo)
{
    char bo_save = *bo;
//    cout << "DoCalc: bo= " << *bo << endl;

    char yn = 'y';
    if (sl == 's') 
	{
	    do 
		{
		    *bo = bo_save;
		    thisCloud.readCloud();
		    // calculating collision coefficients
//		    cout << "DoCalc - entering CalcColl\n";
		    this->CalcColl(thisCloud);
		    // solving the LVG
//		    cout << "DoCalc - entering SolveLvg\n";
		    this->SolveLVG(thisCloud, bo);
		    // printing out
//		    cout << "DoCalc - entering PrintOut\n";
		    this->PrintOut(thisCloud);
		    cout << "\nContinue " << BOLD << "<y/n>" << OFF << " ? ";
		    cin >> yn;
		}
	    while (yn == 'y');
	}
    else 
	{
	    double Tkin,TkinMin,TkinStep,TkinMax,nH2,nH2Min,nH2Fac,nH2Max,Xe,XeMin,XeFac,XeMax,
		Nmol,X_mol,Tdust,NH2,delta_v,Tback,beta_back,tau100mic,Wback,
		Te,EM,WHII,T_cosmic;
	    MinMaxInput_Xmol(TkinMin,TkinStep,TkinMax,nH2Min,nH2Fac,nH2Max,XeMin,XeFac,XeMax,
			X_mol,Tdust,NH2,delta_v,Tback,beta_back,tau100mic,Wback,
			Te,EM,WHII,T_cosmic);
//			    cout << endl;
//			    cout << TkinMin << " " << TkinStep << " " << TkinMax << endl;
//			    cout << nH2Min << " " << nH2Fac << " " << nH2Max << endl;
//			    cout << NmolMin << " " << NmolFac << " " << NmolMax << endl;
	    
	    Tkin = TkinMin;
	    nH2 = nH2Min;
	    Xe = XeMin;
	    do 
		{
		    do 
			{
			    do 
				{
//				    do 
//					{
					    
					    // cout << Tkin << " " << nH2 << " " << Nmol << endl;
//						     // cout << "setting cloud" << endl;
					    *bo = bo_save;
					    Nmol = nH2*X_mol*pc;
					    thisCloud.setCloud(Tkin,nH2,Xe,Nmol,Tdust,NH2,delta_v,
							       Tback,beta_back,tau100mic,Wback,Te,
							       EM,WHII,T_cosmic);
					    // calculating collision coefficients
					    // cout << "collision coefficients " << endl;
					    this->CalcColl(thisCloud);
					    // solving the LVG
					    // cout << "solving"  << endl;
					    this->SolveLVG(thisCloud,bo);
					    // printing out
					    this->PrintOut(thisCloud);
//					}
//				    while (Nmol < NmolMax*NmolFac);
//				    Nmol = NmolMin;
				    Xe *= XeFac;
				}
			    while (Xe < XeMax*XeFac);
			    Xe = XeMin;
			    nH2 *= nH2Fac;
			}
		    while (nH2 < nH2Max*nH2Fac);
		    nH2 = nH2Min;
		    Tkin += TkinStep;
		}
	    while (Tkin < TkinMax+TkinStep);
	}
}
