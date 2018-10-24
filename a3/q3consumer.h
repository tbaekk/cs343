#ifndef __Q3CONSUMER_H__
#define __Q3CONSUMER_H__

#include <uC++.h>
#include "q3buffer.h"
#include "MPRNG.h"
using namespace std;

_Task Consumer {
    BoundedBuffer<int> *buffer;
    const int Delay;
    const int Sentinel;
    int *sum;

    void main() {
         while ( true ) {
            yield( MPRNG()(Delay-1) );
            int next = buffer->remove();
            if ( next == Sentinel )  {
                return;
            } // if
            *sum += next;
        } // while
    }
  public:
    Consumer( BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum ) : 
        buffer(&buffer), Delay(Delay), Sentinel(Sentinel), sum(&sum) {}
};

#endif