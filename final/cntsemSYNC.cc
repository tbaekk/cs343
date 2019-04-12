#include <uC++.h>
#include <uSemaphore.h>
#include <iostream>
using namespace std;

_Task T1 {
    uSemaphore &lk;
    void main() {
      lk.P();
      cout << "S1" << endl;
    }
  public:
    T1( uSemaphore &lk ) : lk(lk) {}
};

_Task T2 {
    uSemaphore &lk;
    void main() {
      lk.P();
      cout << "S2" << endl;
    }
  public:
    T2( uSemaphore &lk ) : lk(lk) {}
};

_Task T3 {
    uSemaphore &lk;
    void main() {
      cout << "S3" << endl;
      lk.V();
      lk.V();
    }
  public:
    T3( uSemaphore &lk ) : lk(lk) {}
};

int main() {
  uSemaphore lck( 0 );
  T1 x( lck );
  T2 y( lck );
  T3 z( lck );
}