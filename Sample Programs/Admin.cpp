#include <iostream>
#include <list>
using namespace std;

_Task Admin {
    uCondition chars;					// waiting users
    list<char> outs;					// only one char in buffer
  public:
    char getChar() {
	cout << "\tAdmin::getChar enter" << endl;
	if ( outs.empty() ) {				// any characters ?
	    cout << "\tAdmin::getChar wait" << endl;
	    chars.wait();				// wait for character
	    cout << "\tAdmin::getChar restart" << endl;
	} // if
	char ch = outs.front();				// copy front char
	outs.pop_front();				// remove front char
	return ch;
    } // Admin::getChar
  private:
    void main() {
	for ( int i = 0; i < 10; i += 1 ) {		// generate N characters
	    cout << "Admin::main before accept" << endl;
	    _Accept( getChar ) {			// wait for user to arrive
		cout << "Admin::main after accept of getChar" << endl;
		outs.push_back( i == 9 ? 'y' : 'x' );	// insert 'x', 'y' at end
		cout << "Admin::main before signalBlock" << endl;
		chars.signalBlock();			// unblock user
		cout << "Admin::main after signalBlock" << endl;
	    } //_Accept
	} // for
    } // Admin::main
}; // Admin

_Task User {
    Admin &adm;

    void main() {
	for ( ;; ) {
	    char ch = adm.getChar();
	  if ( ch == 'y' ) break;			// sentinal character ?
	    cout << "\t\tUser::main ch:" << ch << endl;
	}
    }
  public:
    User( Admin &adm ) : adm( adm ) {}
};

int main() {
    Admin adm;
    User user( adm );
}