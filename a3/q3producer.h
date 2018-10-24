#ifndef __Q3PRODUCER_H__
#define __Q3PRODUCER_H__

#include <uC++.h>
#include "q3buffer.h"
#include "MPRNG.h"
using namespace std;

_Task Producer {
    BoundedBuffer<int> *buffer;
    const int Produce;
    const int Delay;

    void main() {
        for ( int i = 1; i <= Produce; i++ ) {
            yield( MPRNG()(Delay-1) );
            buffer->insert( i );
        } // for
    }
  public:
    Producer( BoundedBuffer<int> &buffer, const int Produce, const int Delay ) :
        buffer(&buffer), Produce(Produce), Delay(Delay) {}
};

#endif