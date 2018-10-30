#include <iostream>
using namespace std;

_Event E {}; // uC++ exception label
void f() {
    _Resume E(); // raise
    // control returns here
    cout << "resumed" << endl;
}

int main() {
    try {
        f();
    } _CatchResume( E ) {
        cout << "handler 1" << endl;
    }
    try {
        f();
    } _CatchResume( E ) {
        cout << "handler 2" << endl;
    }
}
