#include "q3listing.h"

void Listing::main() {
    execCounter = 0;
    curState = fileinfo;
    for (;;) {
        switch(curState) {
            case fileinfo: 
                if (ch == 'd' 
                    || ch == 'D' 
                    || ch == 'b'
                    || ch == 'c'
                    || ch == 'p'
                    || ch == 's'
                    || ch == '-'
                ) {
                    curState = readable;
                } else {
                    _Throw Error();
                } // if
                break;
            case readable:
                if ( ch == 'r' || ch == '-' ) {
                    curState = writable;
                } else {
                    _Throw Error();
                } // if
                break;
            case writable: 
                if ( ch == 'w' || ch == '-' ) {
                    curState = executable;
                } else {
                    _Throw Error();
                } // if
                break;
            case executable: 
                if ( ch =='x' || ch =='-' ) {
                    if ( execCounter >= 2 ) {
                        prevState = executable;
                        curState = whitespace;
                    } else {
                        execCounter++;
                        curState = readable;
                    } // if
                } else {
                    _Throw Error();
                } // if
                break;
            case whitespace:
                if ( ch == ' ' || ch == '\t' ) {
                    if ( prevState == executable ){
                        curState = prevnumsize;
                    } else if ( prevState == prevnumsize ) {
                        curState = prevfilename;
                    } // if
                } else {
                    _Throw Error();
                } // if
                break;
            case prevnumsize: 
                if ( ch == '0' ) {
                    prevState = prevnumsize;
                    curState = whitespace;
                } else if ( ch == ' ' || ch == '\t' ) {
                } else if ( ch >= '1' && ch <= '9' ) {
                    curState = numsize;
                }  else {
                    _Throw Error();
                } // if
                break;
            case numsize:
                if ( ch >= '0' && ch <= '9' ) {
                } else if ( ch == ' ' || ch == '\t' ) {
                    curState = prevfilename;
                } else {
                    _Throw Error();
                } // if
                break;
            case prevfilename: 
                if ( (ch >= 'A' && ch <='Z') || (ch >='a' && ch <= 'z') || ch =='.' || ch =='_' ) {
                    curState = filename;
                } else if ( ch == ' ' || ch == '\t' ) {
                } else {
                    _Throw Error();
                }
                break;
            case filename: 
                if ( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch =='.' || ch =='_' ) {
                } else if ( ch == '*' || ch == '/' ) {
                    curState = kind;
                } else if (ch == '\n') {
                    _Resume Match() _At resumer();
                } else {
                    _Throw Error();
                }
                break;
            case kind:
                if (ch == '\n') {
                    _Resume Match() _At resumer();
                } else { 
                    _Throw Error();
                }
        }
        suspend();
    }
}

void Listing::next( char c ) {
    ch = c; // communicate input
    resume(); // activate
}