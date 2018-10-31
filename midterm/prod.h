#ifndef _PROD_H_
#define _PROD_H_
#include <iostream>
#include "cons.h"
using namespace std;

_Coroutine Prod {
    Cons *c;
    int N, money, receipt;
    void main() { // starter ::main
        // 1st resume starts here
        for ( int i = 0; i < N; i += 1 ) {
            int p1 = rand() % 100; // products
            int p2 = rand() % 100;
            cout << "prod " << p1
            << " " << p2 << endl;
            int status = c->delivery(p1, p2);
            cout << "prod rec $" << money
            << " stat " << status << endl;
            receipt += 1;
        }
        c->stop();
        cout << "prod stops" << endl;
    }
    public:
        int payment( int money ) {
            Prod::money = money;
            resume(); // Prod::main 1st time, then
            return receipt; // prod in Cons::delivery
        }
        void start( int N, Cons &c ) {
            Prod::N = N; Prod::c = &c;
            receipt = 0;
            resume(); // activate main
        }
};

#endif