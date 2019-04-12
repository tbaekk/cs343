#include <uBarrier.h>
#include <uC++.h>
#include <iostream>
using namespace std;

_Task T1 {
    uBarrier &b;
    void main() {
      cout << "S1" << endl;
      b.block();
      cout << "S5" << endl;
    }
  public:
    T1( uBarrier &b ) : b(b) {}
};

_Task T2 {
    uBarrier &b;
    void main() {
      cout << "S2" << endl;
      b.block();
      cout << "S6" << endl;
    }
  public:
    T2( uBarrier &b ) : b(b) {}
};

_Task T3 {
    uBarrier &b;
    void main() {
      cout << "S3" << endl;
      b.block();
      cout << "S7" << endl;
    }
  public:
    T3( uBarrier &b ) : b(b) {}
};

int main() {
  uBarrier b( 3 );
  T1 x( b );
  T2 y( b );
  T3 z( b );
}