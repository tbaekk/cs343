#include "Prod.h"
#include "Cons.h"
#include <iostream>
using namespace std;

void Prod::main() {
    // 1st resume starts here
    for ( int i = 0; i < N; i += 1 ) {
	int p1 = random() % 100;			// generate products
	int p2 = random() % 100;
	cout << "delivers: " << p1 << ", " << p2 << endl;
	int status = c->delivery( p1, p2 );
	cout << " gets payment $" << money << endl;
	cout << " gets status: " << status << endl;
	receipt += 1;
    } // for
    cout << "Prod stops" << endl;
    c->stop();
} // Prod::main

int Prod::payment(int money) {
    Prod::money = money;
    resume();						// restart prod in Cons::delivery
    return receipt;
} // Prod::payment

void Prod::start(int N, Cons *c) {
    Prod::N = N;
    Prod::c = c;
    receipt = 0;
    resume();						// start Prod::main()
} // Prod::start