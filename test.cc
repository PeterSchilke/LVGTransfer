/* 
 * Time-stamp: <2005-12-12 17:39:11 schilke>
 *
 * test.c	-- Peter Schilke Thu Jun 26 1997 (<schilke@mpifr-bonn.mpg.de>)
 *
 */
// using ostringstream constructors.
#include <iostream>
#include <sstream>
#include <string>
//using namespace std;

//void put_test(string&);


int main () {
    
//    std::ostringstream oDataDir;
    std::string DataDir = "./\0";
    std::cout << getenv("LVG_Data") << std::endl;
   
//    if (strcmp(getenv("LVG_Data"),"")) 
//	{
//	    oDataDir << getenv("LVG_Data") << "/\0";
//	    DataDir = oDataDir.str();
//	}
//     cout << getenv("LVG_Data") << endl;
    
//    return 1;
}





