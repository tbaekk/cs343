#include <iostream>
using namespace std;

_Event E {};
_Coroutine C {
    void main() { _Throw E(); }
    public:
        void mem() { resume(); cout << "idk" << endl; } // continue _CatchResume
};

int main() {
    C c;
    try {
        c.mem();
    } _CatchResume( uBaseCoroutine::UnhandledException ) {
        cout << "caught exception from coroutine" << endl;
    } catch( uBaseCoroutine::UnhandledException ) {
        cout << "recover" << endl;
    }
    // continue catch
}
