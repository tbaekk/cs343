#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include <cstdlib>					                    // exit

#include "q3listing.h"

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
        Listing listing;
        if ( line.length() == 0 ) { // blank line
            cout << "'' : Warning! Blank line." << endl; continue; 
        } // if 
        string output = "'" + line + "' : '";
        line = line + "\n";

        for (int i = 0; i < line.length(); i++) {
            try {
                if (i != (line.length() - 1)) {
                    output += line.at(i);
                } // if
                _Enable{ listing.next( line.at(i) ); }
            } _CatchResume( Listing::Match ) {
                cout << output + "' yes" << endl;
            } catch ( uBaseCoroutine::UnhandledException ) {
                output += "' no";
                if ( i < (line.length() - 2) ) {
                    output += ", extraneous characters '" + line.substr(i + 1, (line.length() - 1) - i - 1) + "'";
                } // if
                cout << output << endl;
                break;
            } // try
        } // for
    }
}