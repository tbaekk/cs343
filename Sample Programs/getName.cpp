#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string itostring( long int i ) {
    string str;
    stringstream ss;
    ss << i; // convert int to characters
    return ss.str(); // return characters as a string
}

class C {
  public:
    void print() {
	osacquire( cout ) << "executed by task: " << uThisTask().getName() << " " << &uThisTask() << endl;
    }
};

_Task T {
    char id;
    C    &c;
    string name; // storage must persist for the task's lifetime

    void main() {
	name = "T" + itostring( id );

	setName( name.c_str() ); // setName takes a "char *" not a string
	osacquire( cout ) << getName() << endl;
	c.print();
    }
  public:
    T( char id, C &c ) : c(c), id(id) {}
};

int main() {
    T * tasks[3];
    C c;
    int i;

    for ( i = 0; i < 3; i += 1 ) {
	tasks[i] = new T( i, c );
    } // for
    for ( i = 0; i < 3; i += 1 ) {
	delete tasks[i];
    } // for
}