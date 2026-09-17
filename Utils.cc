//
// Utils.cc	-- Peter Schilke Mon Feb 10 1997
//
//  Time-stamp: <1998-06-05 15:48:29 schilke> 
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Mols.h"

// Subscript Range Error
VectorRangeError::VectorRangeError(int i) 
{
    s = i;
}

int VectorRangeError::badVectorSubscript()
{
  return s;
}

MatrixRangeError::MatrixRangeError(int i, int j) 
{
    s[0] = i;
    s[1] = j;
}

int MatrixRangeError::badMatrixSubscript(int i)
{
  return s[i-1];
}

FileNotFoundError::FileNotFoundError(const char* name)
{
    ostringstream omess(message,ostringstream::out);
    omess << name;
}

char* FileNotFoundError::messFileNotFoundError()
{
    return message;
}

