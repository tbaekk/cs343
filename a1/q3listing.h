#ifndef _Q3LISTING_H_
#define _Q3LISTING_H_

enum States {
  fileinfo,
  readable,
  writable,
  executable,
  whitespace,
  prevnumsize,
  numsize,
  prevfilename,
  filename,
  kind
};

_Coroutine Listing {
        char ch; // character passed by cocaller
        int execCounter; // executable counter to check for last rwx
        States prevState;
        States curState;
        void main(); // coroutine main
    public:
        _Event Match {}; // last character match
        _Event Error {}; // last character invalid
        void next( char c );
};

#endif