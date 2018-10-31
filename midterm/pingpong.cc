#include <iostream>
using namespace std;

_Coroutine PingPong {
    const char *name;
    const unsigned int N;
    PingPong *part;
    void main() { // ping’s starter ::main, pong’s starter ping
        for ( unsigned int i = 0; i < N; i += 1 ) {
            cout << name << endl;
            part->cycle();
        }
    }
    public:
        PingPong( const char *name, unsigned int N, PingPong &part )
        : name( name ), N( N ), part( &part ) {}
        PingPong( const char *name, unsigned int N ) : name( name ), N( N ) {}
        void cycle() { resume(); }
        void partner( PingPong &part ) { PingPong::part = &part; resume(); }
};

int main() {
    enum { N = 20 };
    PingPong ping( "ping", N ), pong( "pong", N, ping );
    ping.partner( pong );
}