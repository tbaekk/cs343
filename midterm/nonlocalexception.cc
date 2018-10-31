#include <iostream>
using namespace std;

_Event E {};
_Coroutine C {
    void main() {
        // initialization, no nonlocal delivery
        try { // setup handlers
            _Enable { // allow nonlocal exceptions
            cout << "before suspend" << endl;
            suspend();
            cout << "after suspend" << endl;
            } // disable all nonlocal exceptions
        } catch( E ) {
            // handle nonlocal exception
            cout << "handle nonlocal exception" << endl;
        }
        // finalization, no nonlocal delivery
    }
    public:
        C() { resume(); } // prime try (not always possible)
        void mem() { resume(); }
};

int main() {
    C c;
    cout << "after init" << endl;
    _Resume E() _At c; // exception pending
    cout << "after exception pending" << endl;
    c.mem(); // trigger exception
    cout << "finish" << endl;
}