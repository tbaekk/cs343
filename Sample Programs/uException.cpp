#include <iostream>
#include <fstream>
using namespace std;

_Event ev {};

_Task Y {
    void main() {
	try {
	    _Enable {
		for ( ;; ) {		// busy wait
		    osacquire( cout ) << "a" << endl;
		    yield();
		} // for
	    } // _Enable
	} catch( ev ) {
	    osacquire( cout ) << "Y caught ev" << endl;
	} // try
    } // main
};

_Task X {
    void main() {
	Y y;
	yield();
	try {
	    ifstream in( "xxx" );	// open non-existing file
	} catch( uFile::Failure ) {
	    osacquire( cout ) << "X caught uFile::Failure, throwing ev at Y" << endl;
	    _Resume ev() _At y;
	} // try
    } // main
};

int main() {
    X x;
}