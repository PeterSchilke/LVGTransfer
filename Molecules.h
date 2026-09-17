/* Molecules	-- Peter Schilke
 *
 * $Header: /home/schilke/cvsroot/transfer/lvg/generic/Molecules.h,v 1.1.1.1 2003/10/15 16:10:22 schilke Exp $
 * $Log: Molecules.h,v $
 * Revision 1.1.1.1  2003/10/15 16:10:22  schilke
 * Generic LVG
 *
 * Revision 1.1.1.1  2001/04/04 08:28:15  schilke
 * version using bn
 *
 */

#ifndef _MOLECULES_H
#define _MOLECULES_H

#endif
typedef double Number;

class Molecule 
{
public:
    Molecule();
    Molecule(int size);
    Number& operator[](int index);
    Number Energy(int index);   // Level energy
    Number gMol(int index);     // statistical weight
    class SubscriptRangeError {};
private:
    int NumberOfLevels;
}

class Transitions
{
public:
    Number A(int size, int size);   // Einstein-A
    Number B(int size, int size);   // Einstein-B
    Number C(int size, int size);   // Collision rate
private:
}


class Linear:
    public Molecule 
{
public:
    Linear();
    Linear(int size);
    int J(int index);    // Quantum number J
    int Index(int J);
private:
    int JMax;
}

class DiAtomicVib:
    public Molecule 
{
public:
    DiAtomicVib();
    DiAtomicVib(int size);
    int v(int index);    // vibrational quantum number             
    int J(int index);    // Quantum number J
    int Index(int v, int J);
private:
    int vMax;
    int JMax;
}

class Sigma:            // e.g. SO
    public Molecule 
{
public:
    Sigma();
    Sigma(int size);
    int N(int index);    // Quantum number N            
    int J(int index);    // Quantum number J
    int Index(int N, int J);
private:
    int NMax;
    int JMax;
}

class PolyAtomicVib:     // with bendig vibrations: hence l-type doubling
    public Molecule 
{
public:
    PolyAtomicVib();
    PolyAtomicVib(int size);
    int v(int index);    // vibrational quantum number             
    int J(int index);    // Quantum number J
    int l(int index);    // Quantum number l
    int Index(int v, int J, int l);
private:
    int vMax;
    int JMax;
    int lMax;
}

class SymmetricRotor:
    public Molecule 
{
public:
    SymmetricRotor();
    SymmetricRotor(int size);
    int J(int index);                        // Quantum number J
    int K(int index);                        // Quantum number K
    int Index(int J, int K);
private:
    int JMax;
    int KMax;
}

class SymmetricRotorVib:
    public Molecule 
{
public:
    SymmetricRotorVib();
    SymmetricRotorVib(int size);
    int v(int index);
    int J(int index);                        // Quantum number J
    int K(int index);                        // Quantum number K
    int Index(int v, int J, int K);
private:
    int vMax;
    int JMax;
    int KMax;
}

class AsymmetricRotor:
    public Molecule 
{
public:
    AsymmetricRotor();
    AsymmetricRotor(int size);
    int J(int index);                        // Quantum number J
    int Kplus(int index);                    // Quantum number K+
    int Kminus(int index);                   // Quantum number K-
    int Index(int J, int Kplus, int Kminus);
private:
    int JMax;
    int KplusMax;
    int KminusMax;
}

class AsymmetricRotorVib:
    public Molecule 
{
public:
    AsymmetricRotorVib();
    AsymmetricRotorVib(int size);
    int v(int index);                        // vibrational quantum number
    int J(int index);                        // Quantum number J
    int Kplus(int index);                    // Quantum number K+
    int Kminus(int index);                   // Quantum number K-
    int Index(int v, int J, int Kplus, int Kminus);
private:
    int vMax;
    
    int JMax;
    int KplusMax;
    int KminusMax;
}

    
    
