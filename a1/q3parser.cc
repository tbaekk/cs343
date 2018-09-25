#include <iostream>
#include "q3parser.h"
#include "q3listing.h"
using namespace std;

void Parser::main() {
    Listing listing;
    //int len = line.length();

    cout << "'" << line << "' " << ": '";
    line = line + "\n";

    for (int i = 0; i < line.length(); i++) {
        try {
            if (i != (line.length() - 1)) {
                cout << line.at(i);
            } // if
            _Enable{ listing.next( line.at(i) ); }
        } _CatchResume( Listing::Match ) {
            cout << "' yes" << endl;
        } catch ( uBaseCoroutine::UnhandledException ) {
            cout << "' no";
            if ( i < (line.length() - 2) ) {
                cout << ", extraneous characters '" << line.substr(i + 1, (line.length() - 1) - i - 1) << "'";
            } // if
            cout << endl;
            break;
        } // try
    }
}

void Parser::run( string str ) {
    line = str;
    resume();
}