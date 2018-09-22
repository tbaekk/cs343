#include <iostream>					// cout
#include <iomanip>					// setw
#include <stdlib.h>					// rand_r
using namespace std;

// Random numbers are often generated globally across a program's execution,
// where the numbers start at some given seed. If the starting value of the
// seed is the same for each program invocation, the same random numbers are
// generated each time the program is run. If the starting value of the seed
// varies for each program invocation, the random numbers differ each time the
// program is run.  The library routine "srand(value)" is used to set the
// starting value of the seed, and routine "rand" generates random numbers from
// the seed value. These two routines set and reset a hidden static global
// variable to remember state between calls.
//
// However, for a concurrent program, globally generating random numbers from
// the starting seed does NOT always produce repeatable results because tasks
// may not execute in a fixed order due to nondeterministic time-slicing.
// Hence, tasks may ask for random numbers in a different order each time the
// program is run, which can result in different execution, even though the
// random numbers are the same each time the program is run. Furthermore, the
// calculation performed by routine "rand" is not atomic, so it could generate
// a non-repeatable sequence given a fixed starting seed or produce lower
// quality random numbers.
//
// To ensure each task generates the same random number, independent of
// nondeterministic time-slicing, requires each task to have its own fixed
// seed. Random numbers are then generated from each private seed using the
// library routine "rand_r(seed)".
//
// If program repeatability of random numbers is unnecessary and the quality of
// the numbers is not crucial, using srand/rand with a varying seed is
// sufficient.

_Task T {
    static unsigned int cnt;				// for uniquely numbering set of tasks
    unsigned int tid;					// individual task number
    unsigned int seed;					// private seed variable

    void main() {
	for ( int i = 0; i < 5; i += 1 ) {
	    unsigned int rnum = rand_r( &seed );	// random integer between 0-RAND_MAX using private seed
	    osacquire( cout ) << tid << " " << setw(10) << rnum << endl;
	    yield( rnum % 10 );				// random integer between 0-9
	}
    }
  public:
    T() {
	tid = cnt += 1;					// unique seed value for each task
#if 1
	seed = tid;					// unique per task (repeatable)
#else
	seed = tid * getpid(); /* or time( NULL ) */	// unique per task (non-repeatable)
#endif
    }
};
unsigned int T::cnt = 0;				// initialize static counter

int main() {
    T t[5];						// create set of identical tasks
}