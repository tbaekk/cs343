#ifndef _Q3LISTING_H_
#define _Q3LISTING_H_

enum parseState {
  start,
  fileinfo,
  rwx1r,
  rwx1w,
  rwx1x,
  rwx2r,
  rwx2w,
  rwx2x,
  rwx3r,
  rwx3w,
  rwx3x,
  whitespacenum,
  zero,
  sizenum,
  whitespacename,
  filename,
  kind
};

_Coroutine Listing {
        char ch; // character passed by cocaller
        parseState state;
        void main(); // coroutine main
    public:
        _Event Match {}; // last character match
        _Event Error {}; // last character invalid
        void next( char c );
};

#endif