#ifndef __PROD_H__
#define __PROD_H__ 1

_Coroutine Cons;					// forward declaration

// Producer full coroutine
_Coroutine Prod {
    Cons *c;						// partner coroutine
    int N;						// number produce
    int money;						// payment received
    int receipt;					// receipt for payment

    void main();					// coroutine main
  public:
    int payment( int money );				// consumer transfers payment in and receives receipt
    void start( int N, Cons *c );			// initialize coroutine
}; // Prod

#endif