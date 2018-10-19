#ifndef _BINSERT_SORT_H_
#define _BINSERT_SORT_H_
#include <iostream>
#include <string>
using namespace std;

template<typename T> _Coroutine Binsertsort {
    T value;                                                            // communication: value being passed down/up the tree
    void main() {
        T pivot = value;
        try {
            _Enable {}
            suspend();

            Binsertsort<T> less;
            Binsertsort<T> greater;
            
            try {
                _Enable {
                    for ( ;; ) {
                        if ( value < pivot )  less.sort( value );
                        if ( value >= pivot ) greater.sort( value );
                        suspend();
                    } // for
                }
            } catch ( Sentinel ) {
            } // try

            _Resume Sentinel() _At less;
            try {
                for ( ;; ) {
                    value = less.retrieve();
                    _Enable {
                        suspend();
                    }
                } // for
            } catch ( Sentinel ) {
            } // try

            value = pivot;
            suspend();

            _Resume Sentinel() _At greater;
            try {
                for ( ;; ) {
                    value = greater.retrieve();
                    _Enable {
                        suspend();
                    }
                } // for
            } catch ( Sentinel ) {
            } // try
        } catch ( Sentinel ) {
        } _Finally {
            _Resume Sentinel() _At resumer();
        }
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
