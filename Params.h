/* Params.h	-- Peter Schilke
 *
 * $Header: /home/schilke/cvsroot/transfer/lvg/generic/Params.h,v 1.1.1.1 2003/10/15 16:10:22 schilke Exp $
 * $Log: Params.h,v $
 * Revision 1.1.1.1  2003/10/15 16:10:22  schilke
 * Generic LVG
 *
 * Revision 1.1.1.1  2001/04/04 08:28:15  schilke
 * version using bn
 *
 */

#ifndef _PARAMS_H
#define _PARAMS_H

#endif
//natural constants
const double Pi       = 3.141592654;
const double c_Light  =  2.99792458e10;
const double k_Boltz  = 1.380622e-16;
const double h_Planck = 6.626196e-27;
const double GHzToK   = h_Planck/k_Boltz * 1e9;      // it's GHz
const double cmToK    = h_Planck/k_Boltz * c_Light;
const double KToau = 1.306e-23/4.3598e-18; // Kelvin to atomic units
const double Ry = 1.09737318e5;  // cm-1: Rydberg constant
const double a0 = 5.2917706e-11; // in m: Bohr constant
const double Dtonat = 1e18*3.355e-30/(1.6021892e-19 * 5.2917706e-11); // dipole moment from Debye to "natural units" : /(e a0)
const double V_conv   = 3.2409e-14;     // conversion factor for vgrad -> cms 
const double pc = 3.0856e18;  // pc in cm

//Constants
const int string_size = 128;
const int maxLev = 500;
const int maxTemp = 50;
const int maxJ = 25;
const int maxVib = 2;   // maximum number of vibrational levels
const int maxP = 2;     // parities
const int maxl = 4;     // up to l=+-2


// Local Variables: ***
// mode: c++ ***
// End:  ***       
 
