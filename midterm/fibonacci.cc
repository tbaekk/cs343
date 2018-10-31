#include <iostream>
using namespace std;

_Coroutine Fibonacci { // : public uBaseCoroutine
    int fn; // used for communication
    void main() { // distinguished member
        int fn1, fn2; // retained between resumes
        fn = 0; fn1 = fn;
        suspend(); // return to last resume
        fn = 1; fn2 = fn1; fn1 = fn;
        suspend(); // return to last resume
        for ( ;; ) {
            fn = fn1 + fn2; fn2 = fn1; fn1 = fn;
            suspend(); // return to last resume
        }
    }
    public:
        int next() {
            resume(); // transfer to last suspend
            return fn;
        }
};

int main() {
    Fibonacci f1, f2; // multiple instances
    for ( int i = 1; i <= 10; i += 1 ) {
        cout << f1.next() << " " << f2.next() << endl;
    }
}
