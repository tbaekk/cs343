#include <iostream>
#include <fstream>
#include <sstream>
#include "q1binsertsort.h"
using namespace std;
#include <cstdlib>					                        // exit

#ifndef TYPE
#define TYPE int
#endif

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " unsorted-file [ sorted-file ] " << endl;
    exit( EXIT_FAILURE );				                    // TERMINATE
} // usage

int main( int argc, char * argv[] ) {
    istream *infile = &cin;				                    // default value
    ostream *outfile = &cout;				                // default value

   switch ( argc ) {
        case 3:
            try {
                outfile = new ofstream( argv[2] );
            } catch( uFile::Failure ) {                     // open failed ?
                cerr << "Error! Could not open output file \"" << argv[4] << "\"" << endl;
                usage( argv );
            } // try
        // FALL THROUGH
        case 2:
            try {
                infile = new ifstream( argv[1] );
            } catch( uFile::Failure ) {
                cerr << "Error! Could not open input file \"" << argv[3] << "\"" << endl;
                usage( argv );
            } // try
        // FALL THROUGH
        case 1:						                        // all defaults
            break;
        default:						                    // wrong number of options
            usage( argv );
    } // switch

    int size;
    TYPE read;         
    for ( ;; ) {
        *infile >> size;					                // read number of elements in the tree
        if ( infile->fail() ) break;			            // failed ?

        Binsertsort<TYPE> binTree;                          // initialize binary tree
        for ( int i = 0; i < size; i++ ) {                  // begin reading numbers from the set of input
            *infile >> read;
            *outfile << read << " ";
            binTree.sort( read );                           // give the value to the root
        } // for

        *outfile << endl;

        _Resume Binsertsort<TYPE>::Sentinel() _At binTree;  // stop input receiving

        for ( int i = 0; i < size; i++ ) {                  // begin retrieving sorted value from the root
            int ret = binTree.retrieve();
            *outfile << ret << " ";                         // print the value retrieved
        } // for

        *outfile << endl << endl;
    } // for

    if ( infile != &cin ) delete infile;		            // close file, do not delete cin!
    if ( outfile != &cout ) delete outfile;		            // close file, do not delete cout!
}
