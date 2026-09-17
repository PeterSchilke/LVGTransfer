//
// Mols	-- Peter Schilke Mon Feb 10 1997
//
//  Time-stamp: <2006-11-27 19:11:28 schilke> 
//
//#include <math>
//#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Params.h"
//#include "Defs.h"

using namespace std;

#ifdef BLITZ

#include <blitz/array.h>
using namespace blitz;

#endif



//Subscript Range Errors
class VectorRangeError 
{
public:
    VectorRangeError(int);
    int badVectorSubscript();
private:
    int s;
};

class MatrixRangeError
{
public:
    MatrixRangeError(int, int);
    int badMatrixSubscript(int);
private:
    int s[2];
};

class FileNotFoundError
{
public:
    FileNotFoundError(const char*);
    char* messFileNotFoundError();
private:
    char message[ string_size ];
};




//Classes

class Cloud
{
public:
    Cloud();
    void readCloud();
    void setCloud(double,double,double,double,double,double,double,double,double,double,double,double,double,double,double);
    double Tkin();
    double nH2();
    double Xe();
    double Nmol();
    double Tdust();
    double NH2();
    double vgrad();
    double delta_v();
    double length();
    double Tback();
    double beta_back();
    double tau100mic();
    double Wback();
    double Te();
    double EM();
    double WHII();
    double T_cosmic();
    
private:
    double val_Tkin;
    double val_nH2;
    double val_Xe;
    double val_Nmol;
    double val_Tdust;
    double val_NH2;
    double val_vgrad;
    double val_delta_v;
    double val_length;
    double val_Tback;
    double val_beta_back;
    double val_tau100mic;
    double val_Wback;
    double val_Te;
    double val_EM;
    double val_WHII;
    double val_T_cosmic;
};

//Molecule
class Levels
{
public:
    int NumberOfLevels();
    double Energy(int);                 // Level energy
    int J(int);                         // Level quantum number
    double g(int);                      // statistical weight
    double n(int);                      // level population
    double getNorm();                     // normalization factor
    void Setn(int,double);             // modify value of n
    double Mu(int);                     // dipole moments
    string MolName();
    void setMolName(string);
protected:
//    char Mol_Name[ string_size ];
    string Mol_Name;
    double* Energy_Of_Level;
    int* J_Of_Level;
    double* g_Of_Level;
    double* n_Of_Level;
    double* b_Of_Level;
    double mu[maxVib*(maxVib+1)/2]; // transitions between all vibrational levels
    int Number_Of_Levels;
    double Jmax;
    double Rc;  // internuclear distance (in Angstrom), needed for electron collisions of HCO+
};


class Transitions:
    public Levels
{
public:
    double frequency(int,int);     // frequency
    double A(int,int);             // Einstein-A
    double B(int,int);             // Einstein-B
    double C(int,int);             // Collision rate
    double Ce(int,int);            // Collison rate with electrons
    double Cr(int,int,int);        // CollRates for interpolation
    double T(int);                  // Temperatures
    void setP(Cloud&,char*);       // Sum A + B*J + n*C
    double getP(int,int);          // Sum A + B*J + n*C
    double calcJ(int,int,Cloud&); // Radiation field 
    int Ntemp();
    void DoCalc(Cloud&,char,char*);
    void DoCalc_Xmol(Cloud&,char,char*);
    void CalcColl(Cloud&);
    void SolveLVG(Cloud&,char*);
    virtual void PrintOut(Cloud&) = 0;
    void printPars();
protected:
//    double Frequency[maxLev][maxLev];
#ifdef BLITZ
    Array<double,2> Frequency;
    Array<double,2> Einstein_A;
    Array<double,2> Einstein_B;
    Array<double,3> CollRates;
    Array<double,2> Collisions;
    Array<double,2> Collisions_e;
    Array<double,2> P;
    Array<double,1> Temperature;
#else
    double Frequency[maxLev][maxLev];
    double Einstein_A[maxLev][maxLev];
    double Einstein_B[maxLev][maxLev];
    double CollRates[maxLev][maxLev][maxTemp];
    double Collisions[maxLev][maxLev];
    double Collisions_e[maxLev][maxLev];
    double P[maxLev][maxLev];
    double Temperature[maxTemp];
#endif

    int N_temp;
    int Convergence;
    ofstream outFile;
    ofstream plotFile;
};

//atomic Oxygen
class atomicOxygen:
    public Transitions {
public:
    atomicOxygen(int, string,string, string, string,double*,double);
    ~atomicOxygen();
    void PrintOut(Cloud&);
    int index(int);              // index as function of J
private:
    int index_J[maxJ];
};
    


//atomic Carbon
class atomicCarbon:
    public Transitions {
public:
    atomicCarbon(int, string,string, string, string,double*,double);
    ~atomicCarbon();
    void PrintOut(Cloud&);
    int index(int);              // index as function of J
private:
    int index_J[maxJ];
};
    

//Linear Vib
class LinearVib:
    public Transitions {
public:
    LinearVib(int, string, string, string, string,double*,double);
    ~LinearVib();
    void PrintOut(Cloud&);
    int v(int);                      // vibrational quantum number
    int index(int,int);              // index as function of v,J
private:
    int* v_Of_Level;
    int index_v_J[maxVib][maxJ];
};

//Linear Vib with l
class LinearVibl:
    public Transitions {
public:
    LinearVibl(int,const string,const string,const string,const string,double*,double);
    ~LinearVibl();
    void PrintOut(Cloud&);
    int v(int);                      // vibrational quantum number
    int l(int);                      // l quantum number
    int index(int,int,int);              // index as function of v,J,l
private:
    int* v_Of_Level;
    int* l_Of_Level;
    int index_v_J_l[maxVib][maxJ][maxl];
};


//Symmetric Rotor
class SymmetricRotor:
    public Transitions {
public:
    SymmetricRotor(int,const string,const string,const string,const string,double*,double);
    ~SymmetricRotor();
    void PrintOut(Cloud&);
    int K(int);                      // K quantum number
    int index(int,int); // index as function of J,K
private:
    int* K_Of_Level;
    int index_J_K[maxJ][maxJ];
};

//ASymmetric Rotor
class AsymmetricRotor:
    public Transitions {
public:
    AsymmetricRotor(int,const string,const string, const string,const string,const string,double*, double);
    ~AsymmetricRotor();
    void PrintOut(Cloud&);
    int Kp(int);                      // K plus quantum number
    int Km(int);                      // K minux quantum number
    int index(int,int,int); // index as function of J,Kp,Km
    double Sif(int,int);             // Einstein-B
private:
    int* Kp_Of_Level;
    int* Km_Of_Level;
    int index_J_Kp_Km[maxJ][maxJ][maxJ];
#ifdef BLITZ
    Array<double,2> S_if;
#else
    double S_if[maxLev][maxLev];
#endif
};

//ASymmetric Rotor with torsions
class AsymmetricRotorT:
    public Transitions {
public:
    AsymmetricRotorT(int,const string,const string, const string,const string,const string,double*, double);
    ~AsymmetricRotorT();
    void PrintOut(Cloud&);
    int K(int);                      // K  quantum number
    int vt(int);                      //  torsional quantum number
    int index(int,int,int,int); // index as function of J,K,vt, + or -
    double Sif(int,int);             // Einstein-B
private:
    int* K_Of_Level;
    int* vt_Of_Level;
    int index_J_K_vt[maxJ][maxJ][maxJ][2];
#ifdef BLITZ
    Array<double,2> S_if;
#else
    double S_if[maxLev][maxLev];
#endif
};

//nh3
class NH3:
    public Transitions {
public:
    NH3(int,const string,const string,const string,const string,double*,double);
    ~NH3();
    void PrintOut(Cloud&);
    int v(int);                      // v2 vibrational quantum number
    int K(int);                      // K quantum number
    int p(int);                      // parity quantum number (inversion transitions)
    int index(int,int,int,int);              // index as function of v,J,K,p
private:
    int* v_Of_Level;
    int* K_Of_Level;
    int* p_Of_Level;
    int index_v_J_K_p[maxVib][maxJ][maxJ][maxP];
};


// function declarations
int Defmol(string,string&,string&,string&,string&,string&,string&,double*,double&);
void print(LinearVib&);
//void printPars(Transitions&,char*);
void print(const string);
void MinMaxInput(double&,double&,double&,double&,double&,double&,double&,double&,
		 double&,double&,double&,double&,double&,double&,double&,double&,
		 double&,double&,double&,double&,double&,double&,double&,double&,
		 double&,double&,double&);
void MinMaxInput_Xmol(double&,double&,double&,double&,double&,double&,double&,double&,
		 double&,double&,double&,double&,double&,double&,
		 double&,double&,double&,double&,double&,double&,double&);

// inline functions


inline
double read(string name)
{
    double value;
    do 
	{
	    char buf[80];
	    
	    cout << "\t" << name << ": "; cin >> buf;
	    value = atof(buf);
	    if (value == 0) 
		{
		    cerr << "\t\tINVALID INPUT: \"" << buf
			 << "\" ,numbers != 0 required. Try again:"
			 << endl;
		}
	    }
    while (value == 0);
    return value;
}

inline
double read0(string name)
{
    double value;
    do 
	{
	    char buf[80];
	    
	    cout << "\t" << name << ": "; cin >> buf;
	    value = atof(buf);
	    if (value < 0) 
		{
		    cerr << "\t\tINVALID INPUT: \"" << buf
			 << "\" ,numbers >= 0 required. Try again:"
			 << endl;
		}
	    }
    while (value < 0);
    return value;
}
    

inline double B_Planck(double T,double f) // Planck-Function
{
    return 2*h_Planck*f*f*f/c_Light/c_Light
	/(exp(f*h_Planck/(k_Boltz*T))-1.);
}

inline double RJ(double T,double f) // Planck-Function
{
    return h_Planck*f/k_Boltz
	/(exp(f*h_Planck/(k_Boltz*T))-1.);
}



inline double kappaCalc(double freq,double n_H2)
#include <cmath>
{    
    double n_d = n_H2/100.; // freq=[Hz],n_d + n_H2=[cm^-3]
    double lambda,slh,Z,b,kap_d;
    // calculate dust absorption coefficient 
    // slh from Zylka R.,1990, Dissertation, Uni Bonn
    // relative Metallicity Z/Z_0 = 2 in galactic center 
    Z = 1.0;
    // Variation of dust absorption cross sections
    if (n_H2 >= 1e6) {
	b = 3.4;
    }
    else {
	b = 1.9;
    }
    
    lambda = 1e6*2.99792458e8/freq;   // in mic
    if (lambda <= 10) 
	{
	    // lambda < 10 mic
	    slh = Z*b*40.0*7e-22*pow(1/40.0,1.5)*pow(1/lambda,1.0);
	}
    else if (lambda <= 40.0) 
	{
	    // 10 mic < lambda < 40 mic
	    slh = Z*b*40.0*7e-22*pow(1/40.0,1.5)*pow(1/lambda,1.0);
	}
    else if (lambda <= 100)
	{
	    // 40 mic < lambda < 100 mic
	    slh = Z*b*7e-22*pow(1/lambda,1.5);
	}
    else {
	//  lambda > 100 mic
	slh = Z*b*7e-21*pow(1/lambda,2.0); 
    }
    // from	: tau_d = N_d*slh    und    tau_d = integral(kappa_d ds) */
    kap_d = n_d * slh;  
    return kap_d;
}



// Local Variables: ***
// mode: c++ ***
// End:  ***       
       
