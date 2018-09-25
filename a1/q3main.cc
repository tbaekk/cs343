#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include <cstdlib>					                    // exit

#include "q3parser.h"

void usage( char * argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ infile ] " << endl;
    exit( EXIT_FAILURE );				                // TERMINATE
} // usage

int main( int argc, char * argv[] ) {
    istream * infile = &cin;				            // default value

    switch ( argc ) {
        case 2:
            try {
                infile = new ifstream( argv[1] );
            } catch( uFile::Failure & ) {
                cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                usage( argv );
            } // try
        case 1:	break;				                    // all defaults
        default: usage( argv );					        // wrong number of options
    } // switch
    
    string line;
    while ( getline(*infile, line) ) {
        Parser parser;
        if ( line.length() == 0 ) { // blank line
            cout << "'' : Warning! Blank line." << endl; continue; 
        }
        parser.run( line );
    }
}