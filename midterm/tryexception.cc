#include <iostream>
using namespace std;

struct E {};
int cnt = 3;
void f( int i ) {
    if ( i == 0 ) throw E();
    try {
        f ( i - 1 );
    } catch ( E ) {
        cout << "caught error" << endl;
        cnt -= 1;
        if ( cnt > 0 ) f( 2 );
    }
}

int main() { f( 2 ); }
