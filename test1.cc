/* 
 * Time-stamp: <2003-10-15 15:17:44 schilke>
 *
 * test.c	-- Peter Schilke Thu Jun 26 1997 (<schilke@mpifr-bonn.mpg.de>)
 *
 */
// using ostringstream constructors.
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void put_test (string &test) {

    ostringstream oss;

    oss << "test";
//    strcpy(test, oss.str());
    test = oss.str();
    cout << test << endl;
    if (test == "test") {
	cout << "yeah!" << endl;
    }
    
    

    return;
}





