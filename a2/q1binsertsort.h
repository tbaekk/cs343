#ifndef _BINSERT_SORT_H_
#define _BINSERT_SORT_H_
#include <iostream>
#include <string>
using namespace std;

template<typename T> _Coroutine Binsertsort {
    T value;                                                            // communication: value being passed down/up the tree
    void main() {
        T pivot = value;
        suspend();

        try {
            _Enable {}
        } catch ( Sentinel ) {
            return;
        }

        Binsertsort<T> less;
        Binsertsort<T> greater;
        
        try {
            for ( ;; ) {
                if ( value < pivot )  less.sort( value );
                if ( value >= pivot ) greater.sort( value );
                _Enable {}
                suspend();
            } // for
        } catch ( Sentinel ) {
            suspend();
            try {
                _Enable {
                    _Resume Sentinel() _At less;
                    for ( ;; ) {
                        value = less.retrieve();
                        _Enable {}
                        suspend();
                    } // for
                }; // enable
            } catch ( Sentinel ) {
            } // try

            value = pivot;
            suspend();

            try {
                _Enable {
                    _Resume Sentinel() _At greater;
                    for ( ;; ) {
                        value = greater.retrieve();
                        _Enable {}
                        suspend();
                    } // for
                }; // enable
            } catch ( Sentinel ) {
            } // try

            _Resume Sentinel() _At resumer();
        } // try
    }
  public:
    _Event Sentinel {};
    void sort( T value ) {          // value to be sorted
        Binsertsort::value = value;
        resume();
    }
    T retrieve() {                  // retrieve sorted value
        resume();
        return value;
    }
};

#endif
