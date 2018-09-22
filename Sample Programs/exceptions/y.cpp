#include "y.h"
#include "x.h"
#include <iostream>
using namespace std;

void Y::main() {
    try {
	_Enable {
	    for (;;) {
		osacquire( cout ) << "a" << endl;
		yield();
	    } // for
	} // _Enable
    } catch( ev ) {
	osacquire( cout ) << "Y caught ev" << endl;
    } // catch
} // main