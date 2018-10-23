#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>                                      // access: rand, srand
#include <cstring>                                      // access: strcmp
#include <uCobegin.h>
using namespace std;
#include <unistd.h>                                     // access: getpid

bool isFileExist = false;

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ xrows (> 0"
	 << ") [ xcols-yrows (> 0"
     << ") [ ycols (> 0"
	 << ") [ processors (> 0) | X-matrix-file Y-matrix-file ] ] ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

int main( int argc, char * argv[] ) {
    istream *fileX, *fileY;
    int xr, xc_yr, yc;
    int processors = 1;

    switch ( argc ) {
        case 6:
            try {
                fileX = new ifstream( argv[4] );
                fileY = new ifstream( argv[5] );
                isFileExist = true;
            } catch( uFile::Failure ) {                 // open failed ?
                cerr << "Error! Could not open input files \"" << argv[4] << " | " << argv[5] << "\"" << endl;
                usage( argv );
            } // try
        // FALL THROUGH
        case 5:
            try {
                if ( !fileX && !fileY ) {
                    processors = stoi( argv[4] );
                }
            } catch ( ... ) {
                usage( argv );
            }
        // FALL THROUGH
        case 4:
            try {
                xr = stoi(argv[1]);
                xc_yr = stoi(argv[2]);
                yc = stoi(argv[3]);
                break;
            } catch( ... ) {
                usage( argv );
            } // try
        // FALL THROUGH
        default:						                // wrong number of options
            usage( argv );
    } // switch
    
    uProcessor p[processors - 1];                       // number of kernel threads
    
    int *Z[xr], *X[xr], *Y[xc_yr];

    if ( !isFileExist ) {
        
    }
}