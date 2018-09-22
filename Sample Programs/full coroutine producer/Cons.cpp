#include "Cons.h"
#include "Prod.h"
#include <iostream>
using namespace std;

void Cons::main() {
    // 1st resume starts here
    int money = 1;					// amount payed for items
    int receipt;					// receipt for producer
    status = 0;

    for ( ; ! done; ) {
	cout << "receives: " << p1 << ", " << p2 << endl;
	cout << " and pays $" << money << endl;
	status += 1;
	receipt = p.payment( money );
	cout << " gets receipt #" << receipt << endl;
	money += 1;
    } // for
    cout << "Cons stops" << endl;
} // Cons::main

int Cons::delivery(int p1, int p2) {
    Cons::p1 = p1; Cons::p2 = p2;
    resume();						// restart cons in Cons::main first time
    return status;					// and cons in Prod::payment afterwards
} // Cons::delivery

void Cons::stop() {
    done = true;
    resume();						// restart in Prod::payment afterwards
} // Cons::stop