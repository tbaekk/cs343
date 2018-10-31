#include <iostream>
#include "prod.h"
#include "cons.h"
using namespace std;

int main() {
    Prod prod;
    Cons cons( prod );
    prod.start( 5, cons );
}