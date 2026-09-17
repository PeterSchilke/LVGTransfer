//
// J.cc	-- Peter Schilke Wed Jun 25 1997
//
//  Time-stamp: <1998-09-18 14:09:39 schilke> 
//
#include "Mols.h"

double Transitions::calcJ(int i, int f, Cloud &thisCloud)  // Radiation field
{
    double J = 0;
    double f = this.frequency(i,j);

    if (f == 0) return J;
// continuum radiation field
    double B_d = B(T_d, f); // dust radiation field
    double I_inf = B(T_back, f);  // background radiation field
// molecular parameters
    double A = Einstein_A[i][f];  // Einstein-A coefficient
    int I = (i>f) ? i : f; int F = (i>f) ? f : i;  // make I > F
    double ni = n_Of_Level[I];
    double nf = n_Of_Level[F];

    if (A == 0. || ni == 0. || nf == 0.) return I_inf;
// no transition or no levels -> no contribution from line
    
    double gi = g_Of_Level[I];
    double gf = g_Of_Level[F];
    int Ji = J_Of_Level[I];
    int Jf = J_Of_Level[F];

    double R  = nf/ni * gi/gf;
    double delta_f = f/c_Light * delta_v; //delta_v not yet defined!!!!
// molecular absorption coefficient    
    double kap_m_0  = A * c_Light*c_Light/(8*Pi*delta_freq*f*f); 
    double kap_m    = kap_m_0 * ni * (R-1.);
// molecular emission coefficient    
    
