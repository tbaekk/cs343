#include <uSemaphore.h>
#include <iostream>
using namespace std;

_Task X {
    uSemaphore &shared;

    void main() {
	osacquire( cout ) << "before lock grab" << endl;
	shared.P();
	osacquire( cout ) << "after lock grab" << endl;
    }
  public:
    X( uSemaphore & s ) : shared( s ) {}
};

_Task Y {
    uSemaphore &shared;

    void main() {
	osacquire( cout ) << "before lock release" << endl;
	shared.V();
	osacquire( cout ) << "after lock release" << endl;
    }
  public:
    Y( uSemaphore & s ) : shared( s ) {}
};

int main() {
    uSemaphore lock( 0 );
    X x( lock );
    Y y( lock );
}