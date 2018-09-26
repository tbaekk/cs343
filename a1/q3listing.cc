#include "q3listing.h"

/*********** main ***********
    Purpose: A character is checked to see if it's a valid character according
        to the given grammer from the assignment,
        if it is given a invalid character it throws error,
        if it is giveen a valid character the coroutine suspends and resumes until eol.


    Returns: None.


    Errors: Invalid character. Coroutine is terminated.
************************************/

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

    if ( ch == ' ' || ch == '\t' ) {
        while ( ch == ' ' || ch == '\t' ) { // whitespace
            suspend();
        } // while
    } else {
        _Throw Error();
    }

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

    if ( ch == ' ' || ch == '\t' ) {
        while ( ch == ' ' || ch == '\t' ) { // whitespace
            suspend();
        } // while
    } else {
        _Throw Error();
    }

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


/*********** main ***********
    Purpose: A character is consumed and assigned to private member,
        if the coroutine main suspends it resumes the method when the
        method is called again.


    Returns: None.


    Errors: No error.
************************************/

void Listing::next( char c ) {
    ch = c; // communicate input
    resume(); // activate
}