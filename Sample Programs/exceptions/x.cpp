#include "x.h"
#include "y.h"
#include <iostream>
#include <fstream>
using namespace std;

void X::main() {
    Y y;
    try {
	ifstream in( "xxx" );	// Open non-existing file
    } catch( uFile::Failure ) {
	osacquire( cout ) << "X caught uFile::Failure, throwing ev at Y" << endl;
	_Resume ev() _At y;
    } // catch
} // main