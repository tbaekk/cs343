#include <stdio.h>
// using namespace std;

label L;

void f( int i ) {
    for (int j = 0; j < 10; j++) {
        int k = j * 2;
        if ( k > i ) goto L;
        printf"passed");
    }
}

void g ( int i ) {
    for (int j = 0; j < 10; j++) {
        f( j );
        printf("returned from f");
    }
}

void h() {
    L = L1;
    for (int j = 0; j < 10; j++) {
        g( j );
    }
    if ( false ) return;
    L1: printf("exceptional return");
}

int main() {
    h();
}