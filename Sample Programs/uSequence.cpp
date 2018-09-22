#include <iostream>
using namespace std;

struct Node : public uSeqable {				// Node structure for the list of integers
    int value;						// Stored value
    Node( int value ) : value( value ) {}
};

int main() {
    const int NumValues = 10;				// Number of values to generate.
    const int RANGE     = 100;				// Range of random values is [0,100)

    uSequence<Node>  top;				// Doubly linked ordered list of integers
    int              i;					// Loop index
    int              value;				// Randomly generated number to be stored.
    Node             *node;				// Temporary pointer

    srand( (uintptr_t)&uThisTask() );			// Seed the random number generator.
  
    for ( i = 0 ; i < NumValues ; i += 1 ) {
	value = rand() % RANGE;
	cout << "Inserting: " << value << endl;

	// insert in sorted order
	for ( uSeqIter<Node> gen(top); gen >> node && value > node->value; );
	top.insertBef( new Node( value ), node );
    } // for 
    
    for ( uSeqIter<Node> gen(top); gen >> node; ) {	// Delete the value and the list of values.
	top.drop();					// Drop front node.
	cout << node->value << endl;
	delete node;					// Remove node.
    } // for 
} // main 

// Local Variables: 
// compile-command: "u++ -g uSequence.cc" 
// End: