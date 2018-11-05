#include <iostream>
#include "MPRNG.h"

using namespace std;

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ voters (> 0 | 'd'"
	 << ") [ group (> 0 | 'd'"
     << ") [ votes (> 0 | 'd'"
	 << ") [ seed (> 0 | 'd'"
     << ") [ processors (> 0 | 'd') ] ] ] ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

MPRNG mprng;
    
int main( int argc, char * argv[] ) {
    int voters = 6, group = 3, votes = 1, seed = getpid(), processors = 1;

    try {
        switch ( argc ) {
            case 6: if ( strcmp( argv[5], "d" ) != 0 ) {  // default ?
                processors = stoi( argv[5] ); if ( processors <= 0 ) throw 1;
            } // if
            case 5: if ( strcmp( argv[4], "d" ) != 0 ) {  // default ?
                seed = stoi( argv[4] ); if ( seed <= 0 ) throw 1;
            } // if
            case 4: if ( strcmp( argv[3], "d" ) != 0 ) {  // default ?
                votes = stoi( argv[3] ); if ( votes <= 0 ) throw 1;
            } // if
            case 3: if ( strcmp( argv[2], "d" ) != 0 ) {  // default ?
                group = stoi( argv[2] ); if ( group <= 0 ) throw 1;
            } // if
            case 2: if ( strcmp( argv[1], "d" ) != 0 ) {  // default ?
                voters = stoi( argv[1] ); if ( voters <= 0 ) throw 1;
            } // if
            case 1: break;                                // use all defaults
            default: throw 1;
        } // switch
    } catch( ... ) {
        usage ( argv );
    } // try

    mprng.set_seed( seed );


}