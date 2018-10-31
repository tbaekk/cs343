#ifndef _CONS_H_
#define _CONS_H_
#include <iostream>
#include "prod.h"
using namespace std;

_Coroutine Cons {
    Prod &p;
    int p1, p2, status;
    bool done;
    void main() { // starter prod
        // 1st resume starts here
        int money = 1, receipt;
        for ( ; !done; ) {
            cout << "cons " << p1 << " "
            << p2 << " pay $"
            << money << endl;
            status += 1;
            receipt = p.payment(money);
            cout << "cons #"
            << receipt << endl;
            money += 1;
        }
        cout << "cons stops" << endl;
    }
    public:
        Cons(Prod &p) : p(p), status(0), done(false) {}
        int delivery( int p1, int p2 ) {
            Cons::p1 = p1; Cons::p2 = p2;
            resume(); // Cons::main 1st time, then
            return status; // cons in Prod::payment
        }
        void stop() {
            done = true;
            resume(); // activate Prod::payment
        }
};

#endif