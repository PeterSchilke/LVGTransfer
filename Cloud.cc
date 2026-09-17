//
// Mols.h.cc	-- Peter Schilke Mon Feb 10 1997
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Mols.h"


// Cloud

Cloud::Cloud()
{}

void Cloud::readCloud()
{
    cout << endl << "Input Cloud data:" << endl;
    val_Tkin  = read("T_kin    ");
    val_nH2   = read0("n(H_2)   ");
    val_Xe   = read0("X(e)     ");
    val_Nmol  = read("N(mol)   ");
    val_Tdust = read("T_dust   ");
    val_NH2   = read0("N(H_2)   ");
    val_delta_v = read("delta_v  ");
    val_Tback = read("Tback    ");
    val_beta_back = read0("beta_back");
    val_tau100mic = read0("tau100mic");
    val_Wback = read0("Wback    ");
    val_Te = read("Te       ");
    val_EM = read0("EM       ");
    val_WHII = read0("WHII     ");
    val_T_cosmic = read0("T_cosmic ");
    val_length = val_NH2/val_nH2;  // in cm
    cout << endl;
    val_vgrad = val_delta_v * V_conv;
    val_Nmol *= 1e-5 * V_conv;
}

void Cloud::setCloud(double T_kin, double nH2, double Xe, double Nmol, 
		     double Tdust, double NH2, double delta_v, 
		     double Tback, double beta_back, double tau100mic, double Wback,
		     double Te, double EM, double WHII, double T_cosmic)
{
    val_Tkin  = T_kin;
    val_nH2   = nH2;
    val_Xe    = Xe;
    val_Nmol  = Nmol;
    val_Tdust = Tdust;
    val_NH2   = NH2;
    val_delta_v = delta_v;
    val_Tback = Tback;
    val_beta_back = beta_back;
    val_tau100mic = tau100mic;
    val_Wback = Wback;
    val_Te = Te;
    val_EM = EM;
    val_WHII = WHII;
    val_length = val_NH2/val_nH2;  // in cm
    val_vgrad = val_delta_v * V_conv;
    val_Nmol *= 1e-5 * V_conv;
    val_T_cosmic = T_cosmic;
}


double Cloud::Tkin()
{
    return val_Tkin;
}

double Cloud::nH2()
{
    return val_nH2;
}

double Cloud::Xe()
{
    return val_Xe;
}

double Cloud::Nmol()
{
    return val_Nmol;
}

double Cloud::Tdust()
{
    return val_Tdust;
}

double Cloud::NH2()
{
    return val_NH2;
}

double Cloud::vgrad()
{
    return val_vgrad;
}

double Cloud::delta_v()
{
    return val_delta_v;
}

double Cloud::Tback()
{
    return val_Tback;
}

double Cloud::beta_back()
{
    return val_beta_back;
}

double Cloud::tau100mic()
{
    return val_tau100mic;
}

double Cloud::Wback()
{
    return val_Wback;
}

double Cloud::length()
{
    return val_length;
}

double Cloud::Te()
{
    return val_Te;
}

double Cloud::EM()
{
    return val_EM;
}

double Cloud::WHII()
{
    return val_WHII;
}

double Cloud::T_cosmic()
{
    return val_T_cosmic;
}
