//
// setP.cc	-- Peter Schilke Wed Jun 25 1997
//
//  Time-stamp: <2008-02-13 13:10:05 schilke> 
//
#include "Mols.h"
#include <iostream>

void Transitions::setP(Cloud &thisCloud, char* bo)  // Sum A + B*J + n*C
{
//    int i, f;
//    double J=0, A, B, C, nH2, Ce, Xe;
//    cout << "Number of levels in setP:" << Number_Of_Levels << endl;
//    cout << "setP: bo " << *bo << endl;
    
    for (int i=0; i<Number_Of_Levels; i++){
	for (int f=0; f<Number_Of_Levels; f++){
	    double A = this->A(i,f); 
	    double B = this->B(i,f); 
	    double C = this->C(i,f);
	    double Ce = this->Ce(i,f);
	    double Cb =  this->C(f,i);
	    double nH2 = thisCloud.nH2();
	    double Xe = thisCloud.Xe();
//	    cout << "setP: " << i << " " << f << endl;
#ifdef BLITZ
	    P(f,i) = 0;
//	    cout << "setP: 1"<< endl;
	    P(f,i)  = nH2 * (C + Xe * Ce);
//	    cout << "setP: 2"<< endl;
            P(f,i) += A; 
//	    cout << "setP: 3"<< endl;
	    if (*bo == 'b') 
		{
		    P(f,i) += this->calcJ(i,f,thisCloud) * B;
//		    cout << "initializing with Boltzmann population" << endl;
		}
	    
//	    cout << "setP: 4"<< endl;
#else
	    P[f][i] = 0;
	    P[f][i]  = nH2 * (C + Xe * Ce);
            P[f][i] += A; 
	    if (*bo == 'b') 
		{
		    P[f][i] += this->calcJ(i,f,thisCloud) * B;
	    // this is for initialisation: if bo = 'o', one initialises the array to the optically thin case.
//		    cout << "initializing with Boltzmann population" << endl;
		}
#endif
/*
  cout << i << "," << f << ": " << g_Of_Level[i] << " " << g_Of_Level[f] << " " 
  << A << " " << B << " " << this->B(f,i)  << " " <<C << " " << Cb << " "
  << this->calcJ(i,f,thisCloud) << " nH2:"
       << nH2 << " P " << this->getP(f,i) <<  "  " << this->getP(i,f) << " " << Number_Of_Levels << endl;
*/
	}
#ifdef BLITZ
	P(i,i) = 0.;
#else
	P[i][i] = 0.;
#endif
	
	for (int f=0; f<Number_Of_Levels; f++) 
	    {
#ifdef BLITZ
		P(i,i) -= (i == f) ? 0.0 : this->getP(f,i);
#else
		P[i][i] -= (i == f) ? 0.0 : this->getP(f,i);
#endif
	    }
	
    }
    *bo = 'b';
    // this is not elegant: the idea is that it is INITIALIZED as optically thin, but that in the
    // subsequent iterations the stuff is done properly
    // so after the first iteration bo is always 'b', no matter what

}


double Transitions::getP(int i, int f) 
{
#ifdef BLITZ
    return P(i,f);
#else
    return P[i][f];
#endif
}
