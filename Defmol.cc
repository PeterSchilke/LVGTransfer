//
// Defmol.cc	-- Peter Schilke Mon Feb 10 1997
//
//  Time-stamp: <2007-11-14 11:38:23 schilke> 
//

#include <sstream>
#include <string>
#include "Mols.h"

int Defmol(string Mol, string &MolFile, string &ColFile, string &OutFile, 
	   string &PlotFile, string &SifFile, string &Type, double *dipole, double &Rc)
{
    string test;
    string DataDir;
    
    cout << getenv("LVG_Data") << endl;
    
    if (getenv("LVG_Data")) 
	{
	    DataDir = getenv("LVG_Data");
            DataDir = DataDir + "/";
	    cout << DataDir << endl;
	}
    
    if ( Mol == "sio" )
	 {
	     MolFile = DataDir + "/sio.dat";
	     ColFile  = DataDir + "/sio.col";
	     OutFile = "sio.out";
	     PlotFile = "sio.plt";
	     Type = "LinearVib";

	     dipole[0] =  3.0982e-18; // dipole_0
	     dipole[1] = 3.1178e-18;  // dipole_1
	     dipole[2] = 5.1;         // Aif don't know where it comes from
	 }
    else if ( Mol == "co") 
	 {
	     MolFile = DataDir + "co.dat";
	     ColFile = DataDir + "co_para.col";
	     OutFile = "co.out";
	     PlotFile = "co.plt";
	     Type = "LinearVib";

	     dipole[0] =  0.11e-18; // dipole_0
	     dipole[1] = 0.11e-18;  // dipole_1
	     dipole[2] = 0.0;         // unknown 
	 }
    else if ( Mol == "13co") 
	 {
	     MolFile = DataDir + "13co.dat";
	     ColFile = DataDir + "co_para.col";
	     OutFile = "13co.out";
	     PlotFile = "13co.plt";
	     Type = "LinearVib";

	     dipole[0] =  0.11e-18; // dipole_0
	     dipole[1] = 0.11e-18;  // dipole_1
	     dipole[2] = 0.0;         // unknown 
	 }
    else if ( Mol == "c18o") 
	 {
	     MolFile = DataDir + "c18o.dat";
	     ColFile = DataDir + "co_para.col";
	     OutFile = "c18o.out";
	     PlotFile = "c18o.plt";
	     Type = "LinearVib";

	     dipole[0] =  0.11e-18; // dipole_0
	     dipole[1] = 0.11e-18;  // dipole_1
	     dipole[2] = 0.0;         // unknown 
	 }
    else if ( Mol == "cs") 
	 {
	     MolFile = DataDir + "cs.dat";
	     ColFile = DataDir + "cs.col";
	     OutFile = "cs.out";
	     PlotFile = "cs.plt";
	     Type = "LinearVib";

	     dipole[0] = 1.958e-18; // dipole_0
	     dipole[1] = 1.936e-18;  // dipole_1
	     dipole[2] = 4.2e-10;    // unknown 
	 }
    else if ( Mol == "oi") 
	 {
	     MolFile = DataDir + "oi.dat";
	     ColFile = DataDir + "oi.col";
	     OutFile = "oi.out";
	     PlotFile = "oi.plt";
	     Type = "atomicOxygen";

	     dipole[0] = 0; // dipole_0
	     dipole[1] = 0;  // dipole_1
	     dipole[2] = 0;    // unknown 
	 }
    else if ( Mol == "ci") 
	 {
	     MolFile = DataDir + "ci.dat";
	     ColFile = DataDir + "ci.col";
	     OutFile = "ci.out";
	     PlotFile = "ci.plt";
	     Type = "atomicCarbon";

	     dipole[0] = 0; // dipole_0
	     dipole[1] = 0;  // dipole_1
	     dipole[2] = 0;    // unknown 
	 }
    else if ( Mol == "hco+") 
	 {
	     MolFile = DataDir + "hco+.dat";
	     ColFile = DataDir + "hco+.col";
	     OutFile = "hco+.out";
	     PlotFile = "hco+.plt";
	     Type = "LinearVib";

	     dipole[0] = 3.3e-18; // dipole_0
	     dipole[1] = 3.1178e-18;  // dipole_1
	     dipole[2] = 0.0;         // unknown
	     Rc = 2.2;
	 }
    else if ( Mol == "dco+") 
	 {
	     MolFile = DataDir + "dco+.dat";
	     ColFile = DataDir + "hco+.col";
	     OutFile = "dco+.out";
	     PlotFile = "dco+.plt";
	     Type = "LinearVib";

	     dipole[0] = 3.3e-18; // dipole_0
	     dipole[1] = 3.1178e-18;  // dipole_1
	     dipole[2] = 0.0;         // unknown
	 }
    else if ( Mol == "hc3n") 
	 {
	     MolFile = DataDir + "hc3n.dat";
	     ColFile = DataDir + "hc3n.col";
	     OutFile = "hc3n.out";
	     PlotFile = "hc3n.plt";
	     Type = "LinearVib";

	     dipole[0] = 3.724e-18; // dipole_0
	     dipole[1] = 0.0;  // dipole_1
	     dipole[2] = 0.0;         // unknown 
	 }
    else if ( Mol == "hcn") 
	 {
	     MolFile = DataDir + "hcn.dat";
	     ColFile = DataDir + "hcn_g.col";
	     OutFile = "hcn.out";
	     PlotFile = "hcn.plt";
	     Type = "LinearVibl";

	     dipole[0] = 2.985e-18; // dipole_0
	     dipole[1] = 2.957e-18;  // dipole_1
	     dipole[2] = 0.19e-18;         // dipole_2
	 }
    else if ( Mol == "hnc") 
	 {
	     MolFile = DataDir + "hnc.dat";
	     ColFile = DataDir + "hcn_g.col";
	     OutFile = "hnc.out";
	     PlotFile = "hnc.plt";
	     Type = "LinearVibl";

	     dipole[0] = 3.05e-18; // dipole_0
	     dipole[1] = 0;  // dipole_1
	     dipole[2] = 0;         // dipole_2
	 }
    else if ( Mol == "dcn") 
	 {
	     MolFile = DataDir + "dcn.dat";
	     ColFile = DataDir + "hcn_g.col";
	     OutFile = "dcn.out";
	     PlotFile = "dcn.plt";
	     Type = "LinearVibl";

	     dipole[0] = 2.990198e-18; // dipole_0
	     dipole[1] = 2.957e-18;  // dipole_1 - same as HCN
	     dipole[2] = 0.23;         // dipole_2 - same as HCN
	 }
    else if ( Mol == "dcn_hfs") 
	 {
	     MolFile = DataDir + "dcn.dat";
	     ColFile = DataDir + "hcn_g.col";
	     OutFile = "dcn_hfs.out";
	     PlotFile = "dcn_hfs.plt";
	     Type = "LinearVibl";

	     dipole[0] = 2.990198e-18; // dipole_0
	     dipole[1] = 2.957e-18;  // dipole_1 - same as HCN
	     dipole[2] = 0.23;         // dipole_2 - same as HCN
	 }
    else if ( Mol == "nh3-o") 
	 {
	     MolFile = DataDir + "nh3-o.dat";
	     ColFile = DataDir + "nh3-o.col";
	     OutFile = "nh3-o.out";
	     PlotFile = "nh3-o.plt";
	     Type = "NH3";

	     dipole[0] = 1.47147e-18; // dipole_0 shimoda Appl. Phys. 21, 181 (1980)
	     dipole[1] = 1.248e-18;  // dipole_1 shimoda Appl. Phys. 21, 181 (1980)
	     dipole[2] = 0.23;         // dipole_2 - freund, oka Phys. Rev. A 23, 6 (1976)
	 }
    else if ( Mol == "nh3-p") 
	 {
	     MolFile = DataDir + "nh3-p.dat";
	     ColFile = DataDir + "nh3-p.col";
	     OutFile = "nh3-p.out";
	     PlotFile = "nh3-p.plt";
	     Type = "NH3";

	     dipole[0] = 1.47147e-18; // dipole_0 shimoda Appl. Phys. 21, 181 (1980)
	     dipole[1] = 1.248e-18;  // dipole_1 shimoda Appl. Phys. 21, 181 (1980)
	     dipole[2] = 0.23;         // dipole_2 - freund, oka Phys. Rev. A 23, 6 (1976)
	 }
    else if ( Mol == "h2co-p") 
	 {
	     MolFile = DataDir + "h2co-p.dat";
	     ColFile = DataDir + "h2co-p.col";
	     SifFile = DataDir + "h2co-p.sif";
	     OutFile = "h2co-p.out";
	     PlotFile = "h2co-p.plt";
	     Type = "AsymmetricRotor";

	     dipole[0] =  2.34e-18; // 
	     dipole[1] = 0.;  //
	     dipole[2] = 0.;    
		 }
    else if ( Mol == "h2co-o") 
	 {
	     MolFile = DataDir + "h2co-o.dat";
	     ColFile = DataDir + "h2co-o.col";
	     SifFile = DataDir + "h2co-o.sif";
	     OutFile = "h2co-o.out";
	     PlotFile = "h2co-o.plt";
	     Type = "AsymmetricRotor";

	     dipole[0] =  2.34e-18; //
	     dipole[1] = 0.;  //
	     dipole[2] = 0.;    
	 }
    else if ( Mol == "ch3oh-a") 
	 {
	     MolFile = DataDir + "ch3oh-a.dat";
	     ColFile = DataDir + "ch3oh-a.col";
	     SifFile = DataDir + "ch3oh-a.sif";
	     OutFile = "ch3oh-a.out";
	     PlotFile = "ch3oh-a.plt";
	     Type = "AsymmetricRotorT";

	     dipole[0] =  0.; // line strengths read
	     dipole[1] = 0.;  //
	     dipole[2] = 0.;    
	 }
    else if ( Mol == "ch3oh-e") 
	 {
	     MolFile = DataDir + "ch3oh-e.dat";
	     ColFile = DataDir + "ch3oh-e.col";
	     SifFile = DataDir + "ch3oh-e.sif";
	     OutFile = "ch3oh-e.out";
	     PlotFile = "ch3oh-e.plt";
	     Type = "AsymmetricRotorT";

	     dipole[0] = 0.; // line strength read
	     dipole[1] = 0.;  //
	     dipole[2] = 0.;    
	 }
    else 
	{
	    cout << "Molecule not supported" << endl;
	    return -1 ;
	}
/*
    cout << "File: " << MolFile   << endl;
    cout << "File: " << ColFile  << endl;
    cout << "File: " << SifFile  << endl;
    cout << "File: " << OutFile  << endl;
    cout << "File: " << PlotFile  << endl;
    cout << "Type: " << Type  << endl;
    
*/
    
    return 0;
}
