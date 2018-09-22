#ifndef __CONS_H__
#define __CONS_H__ 1

_Coroutine Prod;					// forward declaration

// Consumer full coroutine
_Coroutine Cons {
    Prod &p;						// partner coroutine
    int p1, p2;						// items to be consumed
    int status;						// indicate delivery status
    bool done;						// termination flag

    void main();					// coroutine main
  public:
    Cons( Prod &p ) : p( p ), done( false ) {}
    int delivery( int p1, int p2 );			// producer delivers items to be consumed
    void stop();					// terminate coroutine
}; // Cons

#endif