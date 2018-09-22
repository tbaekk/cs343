#include "Prod.h"
#include "Cons.h"

// main to start producer/consumer coroutines and waits for termination
int main() {
    Prod prod;
    Cons cons( prod );
    prod.start( 5, &cons );
} // main