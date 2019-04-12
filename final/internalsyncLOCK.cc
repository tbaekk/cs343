#include <uC++.h>
#include <iostream>
using namespace std;

bool done = false;

_Task T1 {
    uOwnerLock &mlk;
    uCondLock &clk;
    void main() {
      mlk.acquire(); // prevent lost signal
      if ( ! done )  { // signal occurred ?
        cout << "T1: before wait " << endl;
        // signal not occurred
        clk.wait( mlk ); // atomic wait/release
        // mutex lock re-acquired after wait
        cout << "T1: after wait " << endl;
      }
      mlk.release(); // release either way
      cout << "T1: finished" << endl;
    }
  public:
    T1( uOwnerLock &mlk, uCondLock &clk ) : mlk(mlk), clk(clk) {}
};

_Task T2 {
    uOwnerLock &mlk;
    uCondLock &clk;
    void main() {
      cout << "T2: started " << endl;
      mlk.acquire(); // prevent lost signal
      done = true; // remember signal occurred
      cout << "T2: before signal" << endl;
      clk.signal(); // signal lost if not waiting
      cout << "T2: after signal" << endl;
      mlk.release();
    }
  public:
    T2( uOwnerLock &mlk, uCondLock &clk ) : mlk(mlk), clk(clk) {}
};

int main() {
  uOwnerLock mlk;
  uCondLock clk;
  T1 t1( mlk, clk );
  T2 t2( mlk, clk );
}