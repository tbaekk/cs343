#ifndef _BINSERT_SORT_H_
#define _BINSERT_SORT_H_

template<typename T> _Coroutine Binsertsort {
    T value;                                                            // communication: value being passed down/up the tree
    void main() {
        Binsertsort<T> greater;
        Binsertsort<T> less;
        
        try {
            T pivot = value;
            suspend();  // less1 (P: binTree) & right1 (P: binTree)

            for ( ;; ) {
                if ( value < pivot )  _Enable{ less.sort( value ); };
                if ( value >= pivot ) _Enable{ greater.sort( value ); };
                suspend();
            }
            suspend();  // binTree
        } catch ( Binsertsort<TYPE>::Sentinel ) {
        } // try

        try {
            _Enable {
                 _Throw Binsertsort<TYPE>::Sentinel() _At less;
                for ( ;; ) {
                    value = less.retrieve();
                    suspend();
                } // for
            }; // enable
        } catch ( Binsertsort<TYPE>::Sentinel ) {
        } // try

        value = pivot;
        suspend();

        try {
            _Enable {
                _Throw Binsertsort<TYPE>::Sentinel() _At greater;
                for ( ;; ) {
                    value = greater.retrieve();
                    suspend();
                } // for
            };
        } catch ( Binsertsort<TYPE>::Sentinel ) {
        } // try

        _Resume Binsertsort<TYPE>::Sentinel() _AT resumer();
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
