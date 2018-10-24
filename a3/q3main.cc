#include <iostream>
#include "q3buffer.h"
#include "q3producer.h"
#include "q3consumer.h"
using namespace std;
#include <unistd.h>                                     // access: getpid


void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ Cons (> 0"
	 << ") [ Prods (> 0"
     << ") [ Produce (> 0"
	 << ") [ BufferSize (> 0 "
     << ") [ Delays (> 0 ) ] ] ] ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

void isValidInput( int argc, int cons, int prods, int produce, int bufferSize, int delay ) {
    if ( argc > 6 || cons <= 0 || prods <= 0 || produce <= 0 || bufferSize <= 0 || delay <= 0 ) {
        throw exception();
    }
}

int main( int argc, char * argv[] ) {
    int cons = 5, prods = 3, produce = 10, bufferSize = 10, delay = 0;

    switch ( argc ) {
        case 6:
            delay = stoi( argv[5] );
        // FALL THROUGH
        case 5:
            bufferSize = stoi( argv[4] );
        // FALL THROUGH
        case 4:
            produce = stoi( argv[3] );
        // FALL THROUGH
        case 3:
            prods = stoi( argv[2] );
        // FALL THROUGH
        case 2:
            cons = stoi( argv[1] );
        default:
            try {
                if ( delay == 0 ) {
                    delay = cons + prods;
                } // if
                isValidInput( argc, cons, prods, produce, bufferSize, delay );
            } catch ( ... ) {
                usage( argv );
            } // try
    } // switch

    #ifdef __U_MULTI__
        uProcessor p[3] __attribute__(( unused )); // create 3 kernel thread for a total of 4
    #endif // __U_MULTI__

    int i = 0;
    
    // Setup the tasks
    BoundedBuffer<TYPE> buffer(bufferSize);

    Producer *producers[prods];
    for ( ; i < prods; i++ ) {
        producers[i] = new Producer(buffer, produce, delay);
    } // for

    int sum = 0;
    Consumer *consumers[cons];
    for ( i = 0; i < cons; i++ ) {
        consumers[i] = new Consumer(buffer, delay, SENTINEL, sum);
    } // for

    for ( i = 0; i < prods; i++ ) {
        delete producers[i];
    } // for

    for ( i = 0; i < cons; i++ ) {
        buffer.insert(SENTINEL);
    } // for

    for ( i = 0; i < cons; i++ ) {
        delete consumers[i];
    } // for

    cout << "total: " << sum << endl;
}