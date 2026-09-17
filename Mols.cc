//
// Mols.h.cc	-- Peter Schilke Mon Feb 10 1997
//
//  Time-stamp: <2005-12-22 16:26:27 schilke> 
//

#include <sstream>
#include "Mols.h"

// Levels
//Levels::~Levels() {}  // virtual destructor

int Levels::NumberOfLevels()
{
    return Number_Of_Levels;
}

double Levels::Energy(int index)
{
    if (index < 0 || index >= NumberOfLevels()) throw VectorRangeError(index);
    return Energy_Of_Level[index];
}

int Levels::J(int index)
{
    if (index < 0 || index >= NumberOfLevels()) throw VectorRangeError(index);
    return J_Of_Level[index];
}

double Levels::g(int index)
{
    if (index < 0 || index >= NumberOfLevels()) throw VectorRangeError(index);
    return g_Of_Level[index];
}

double Levels::n(int index)
{
    if (index < 0 || index >= NumberOfLevels()) throw VectorRangeError(index);
    return n_Of_Level[index];
}

double Levels::getNorm()
{
    return n_Of_Level[NumberOfLevels()];
}

void Levels::Setn(int index, double value)
{
   if (index < 0 || index >= NumberOfLevels()) throw VectorRangeError(index);
    n_Of_Level[index] = value;
}

double Levels::Mu(int index)
{
    if (index < 0 || index >= maxVib) throw VectorRangeError(index);
    return mu[index];
}

string Levels::MolName()
{
//    cout << "Mol_Name " << Mol_Name << endl;
    return Mol_Name;
}

void Levels::setMolName(string Mol)
{
    Mol_Name = Mol;
}


//Transition
double Transitions::A(int i, int j)
{
#ifdef BLITZ
    return Einstein_A(i,j);
#else
    return Einstein_A[i][j];
#endif
}

double Transitions::B(int i, int j)
{
#ifdef BLITZ
    return Einstein_B(i,j);
#else
    return Einstein_B[i][j];
#endif
}

double Transitions::C(int i, int j)
{
#ifdef BLITZ
    return Collisions(i,j);
#else
    return Collisions[i][j];
#endif
}

double Transitions::Ce(int i, int j)
{
#ifdef BLITZ
    return Collisions_e(i,j);
#else
    return Collisions_e[i][j];
#endif
}

double Transitions::Cr(int i, int j, int t)
{
#ifdef BLITZ
    return CollRates(i,j,t);
#else
    return CollRates[i][j][t];
#endif
}

double Transitions::T(int index)
{
#ifdef BLITZ
    return Temperature(index);
#else
    return Temperature[index];
#endif
}

double Transitions::frequency(int i, int j)
{
#ifdef BLITZ
    return Frequency(i,j);
#else
    return Frequency[i][j];
#endif
}

int Transitions::Ntemp()
{
    return N_temp;
}


