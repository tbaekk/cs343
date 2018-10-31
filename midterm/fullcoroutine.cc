#include <iostream>
using namespace std;

_Coroutine Fc {
    void main() { // starter ::main
        cout << "before mem()" << endl;
        mem(); // ?
        cout << "after mem()" << endl;
        cout << "before resume2" << endl;
        resume(); // ?
        cout << "after resume2" << endl;
        cout << "before suspend" << endl;
        suspend(); // ?
        cout << "after suspend" << endl;
    } // ?
    public:
        void mem() { 
            cout << "before resume1" << endl;
            resume();
            cout << "after resume1" << endl;
        }
};
int main() {
    Fc fc;
    fc.mem();
}