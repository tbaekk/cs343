#include <iostream>
using namespace std;

int main() {
    L1: {
        int i = 1;
        L2: switch (i ) {
            case 5:
            case 1:
                L3: for ( ;; ) {
                    break L3;
                    break L2;
                    break L1;
                }
                cout << "end of L3" << endl;
        }
        cout << "end of L2" << endl;
    }
    cout << "end of L1" << endl;
}