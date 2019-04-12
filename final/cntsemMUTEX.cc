#include <uC++.h>
#include <uSemaphore.h>
#include <iostream>
using namespace std;

_Task T {
    uSemaphore &lk;
    unsigned int i;
    void main() {
      lk.P();
      cout << i << endl; 
      lk.V();
    }
  public:
    T( uSemaphore &lk, unsigned int i ) : lk(lk), i(i) {}
};

int main() {
  uSemaphore lck( 3 );
  T x( lck, 2 ), y( lck, 3 ), z( lck, 1 );
}