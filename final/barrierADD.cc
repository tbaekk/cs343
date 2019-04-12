#include <uBarrier.h>
#include <uC++.h>
#include <iostream>
using namespace std;

_Cormonitor Accumulator : public uBarrier {
    int total_;
    uBaseTask *Nth_;
  public:
    Accumulator( int rows ) : uBarrier( rows ), total_( 0 ), Nth_( nullptr ) {}
    void block( int subtotal ) { total_ += subtotal; uBarrier::block(); }
    void last() { Nth_ = &uThisTask(); } // remember Nth task
    int total() { return total_; }
    uBaseTask *Nth() { return Nth_; }
};

_Task Adder {
    int *row, size;
    Accumulator &acc;
    void main() {
      int subtotal = 0;
      for ( unsigned int r = 0; r < size; r += 1 ) subtotal += row[r];
      acc.block( subtotal ); // provide subtotal; wait for completion
    }
  public:
    Adder( int row[ ], int size, Accumulator &acc ) :
    size( size ), row( row ), acc( acc ) {}
};

int main() {
  enum { rows = 10, cols = 10 };
  int matrix[rows][cols];
  Adder *adders[rows];
  Accumulator acc( rows ); // barrier synchronizes each summation
  // read matrix
  for ( unsigned int r = 0; r < rows; r += 1 ) {
    adders[r] = new Adder( matrix[r], cols, acc );
  }
  for ( unsigned int r = 0; r < rows; r += 1 ) {
    delete adders[r];
  }
  cout << acc.total() << " " << acc.Nth() << endl;
}