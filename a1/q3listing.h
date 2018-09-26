#ifndef _Q3LISTING_H_
#define _Q3LISTING_H_

_Coroutine Listing {
        char ch; // character passed by cocaller
        void main(); // coroutine main
    public:
        _Event Match {}; // last character match
        _Event Error {}; // last character invalid
        void next( char c );
};

#endif