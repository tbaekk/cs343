#include "q3listing.h"

void Listing::main() {
    state = start;
    for (;;) {
      switch(state) {
        case start: 
        if (ch=='d' || ch=='D' || ch=='b' || ch=='c' || ch=='p' || ch=='s' || ch=='-') {
          state = fileinfo;
        } else {
          _Throw Error();
        }
        break;

        case fileinfo:
        if (ch=='r' || ch=='-') {
          state = rwx1r;
        } else {
          _Throw Error();
        }
        break;

        case rwx1r: 
        if (ch=='w' || ch=='-') {
          state = rwx1w;
        } else {
          _Throw Error();
        }
        break;

        case rwx1w: 
        if (ch=='x' || ch=='-') {
          state = rwx1x;
        } else {
          _Throw Error();
        }
        break;

        case rwx1x: 
        if (ch=='r' || ch=='-') {
          state = rwx2r;
        } else {
          _Throw Error();
        }
        break;

        case rwx2r: 
        if (ch=='w' || ch=='-') {
          state = rwx2w;
        } else {
          _Throw Error();
        }
        break;

        case rwx2w: 
        if (ch=='x' || ch=='-') {
          state = rwx2x;
        } else {
          _Throw Error();
        }
        break;

        case rwx2x: 
        if (ch=='r' || ch=='-') {
          state = rwx3r;
        } else {
          _Throw Error();
        }
        break;

        case rwx3r: 
        if (ch=='w' || ch=='-') {
          state = rwx3w;
        } else {
          _Throw Error();
        }
        break;

        case rwx3w: 
        if (ch=='x' || ch=='-') {
          state = rwx3x;
        } else {
          _Throw Error();
        }
        break;

        case rwx3x: 
        if (ch==' ' || ch=='\t') {
          state = whitespacenum;
        } else {
          _Throw Error();
        }
        break;

        case whitespacenum: 
        if (ch=='0') {
          state = zero;
        } else if (ch==' ' || ch =='\t') {
        } else if (ch >= '1' && ch <= '9') {
          state = sizenum;
        }  else {
          _Throw Error();
        }
        break;

        case zero: 
        if (ch==' ' || ch =='\t') {
          state = whitespacename;
        } else {
          _Throw Error();
        }
        break;

        case sizenum: 
        if (ch >= '0' && ch <= '9') {
        } else if (ch==' ' || ch =='\t') {
          state = whitespacename;
        } else {
          _Throw Error();
        }
        break;

        case whitespacename: 
        if ((ch >= 'A' && ch <='Z') || (ch >='a' && ch <= 'z') || ch=='.' || ch=='_') {
          state = filename;
        } else if (ch==' ' || ch =='\t') {
        } else {
          _Throw Error();
        }
        break;

        case filename: 
        if ((ch >= 'A' && ch <='Z') || (ch >='a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch=='.' || ch=='_') {
        } else if (ch=='*' || ch =='/') {
          state = kind;
        } else if (ch=='\n') {
          _Resume Match() _At resumer();
        } else {
          _Throw Error();
        }
        break;

        case kind:
        if (ch=='\n') {
          _Resume Match() _At resumer();
         } else { _Throw Error(); }
      }

      suspend();
    }
}

void Listing::next( char c ) {
    ch = c; // communicate input
    resume(); // activate
}