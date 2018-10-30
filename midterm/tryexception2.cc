#include <iostream>
using namespace std;

struct E1 {};
struct E2 {};
struct E3 {};
struct E4 {};
struct E5 {};
struct E6 {};
struct E7 {};
struct E8 {};
struct E9 {};

void f() {
    try {
        try {
            try {
                 {
                    try { 
                        throw E5();
                    } catch( E7 ) {                        
                    } catch( E8 ) {                        
                    } catch( E9 ) {                        
                    }
                 } 
            } catch( E4 ) {
            } catch( E5 ) {
                throw;
            } catch ( E6 ) {
            }
        } catch( E3 ) {            
        }
    } catch( E5 ) {
        cout << "hello" << endl;
    } catch( E2 ) {}
}

int main() { f(); }
