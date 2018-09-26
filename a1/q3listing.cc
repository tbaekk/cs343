#include "q3listing.h"

void Listing::main() {
    if (ch == 'd' 
        || ch == 'D' 
        || ch == 'b'
        || ch == 'c'
        || ch == 'p'
        || ch == 's'
        || ch == '-'
    ) { // fileinfo
        suspend();
    } else {
        _Throw Error();
    } // if

    for ( int i = 0; i < 3 ; i++ ) { // rwx
        if ( ch == 'r' || ch == '-' ) {
            suspend();
        } else {
            _Throw Error();
        } // if

        if ( ch == 'w' || ch == '-' ) {
            suspend();
        } else {
            _Throw Error();
        } // if

        if ( ch == 'x' || ch == '-' ) {
            suspend();
        } else {
            _Throw Error();
        } // if
    } // for

    while ( ch == ' ' || ch == '\t' ) { // whitespace
        suspend();
    } // while

    if ( ch == '0' ) { // size
        suspend();
    } else if ( ch >= '1' && ch <= '9' ) {
        while ( ch >= '0' && ch <= '9' ) {
            suspend();
            if ( ch == ' ' || ch == '\t' ) {
                break;
            }
        }
    } // if

    while ( ch == ' ' || ch == '\t' ) { // whitespace
        suspend();
    } // while

    if ((ch >= 'A' && ch <='Z')
        || (ch >='a' && ch <= 'z')
        || ch =='.' || ch =='_'
    ) {
        suspend();
        while ( (ch >= 'A' && ch <= 'Z') 
            || (ch >= 'a' && ch <= 'z') 
            || (ch >= '0' && ch <= '9') 
            || ch =='.' || ch =='_'
        ) {
            suspend();
        } // while
    } else {
        _Throw Error();
    } // if

    if ( ch == '*' || ch == '/' ) { // kind
        suspend();
    } // if

    if ( ch == '\n' ) { // eol
         _Resume Match() _At resumer();
    } else {
        _Throw Error();
    } // if
}

void Listing::next( char c ) {
    ch = c; // communicate input
    resume(); // activate
}