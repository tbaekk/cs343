#include <iostream>
#include <cstdlib>                                      // access: rand, srand
#include <cstring>                                      // access: strcmp
#include <variant>                                      // access: variant
using namespace std;
#include <unistd.h>                                     // access: getpid

struct Er1 { short int code; };
struct Er2 { int code; };
struct Er3 { long int code; };

int eperiod = 10000;                                    // error period

variant<double,Er1,Er2,Er3> operator+( variant<double,Er1,Er2,Er3> v, double i ) {
    return holds_alternative<double>(v) ? get<double>(v) + i : v;
}

variant<double,Er1,Er2,Er3> rtn1( double i ) {
    variant<double,Er1,Er2,Er3> result = i;
    if ( rand() % eperiod == 0 ) {
        result = Er1{ (short int)rand() };
    } // if
    return result;
}
variant<double,Er1,Er2,Er3> rtn2( double i  ) {
    variant<double,Er1,Er2,Er3> result = i;
    if ( rand() % eperiod == 0 ){
        result = Er2{ rand() };
    } else {
        result = rtn1( i );
    } // if
    return result + i;
}
variant<double,Er1,Er2,Er3> rtn3( double i  ) {
    variant<double,Er1,Er2,Er3> result = i;
    if ( rand() % eperiod == 0 ) {
        result = Er3{ rand() };
    } else {
        result = rtn2( i );
    } // if
    return result + i;
}
int main( int argc, char * argv[] ) {
    int times = 100000000, seed = getpid();             // default values
    try {
        switch ( argc ) {
          case 4: if ( strcmp( argv[3], "d" ) != 0 ) {  // default ?
                seed = stoi( argv[3] ); if ( seed <= 0 ) throw 1;
            } // if
          case 3: if ( strcmp( argv[2], "d" ) != 0 ) {  // default ?
                eperiod = stoi( argv[2] ); if ( eperiod <= 0 ) throw 1;
            } // if
          case 2: if ( strcmp( argv[1], "d" ) != 0 ) {  // default ?
                times = stoi( argv[1] ); if ( times <= 0 ) throw 1;
            } // if
          case 1: break;                                // use all defaults
          default: throw 1;
        } // switch
    } catch( ... ) {
        cerr << "Usage: " << argv[0] << " [ times > 0 | d [ eperiod > 0 | d [ seed > 0 ] ] ]" << endl;
        exit( EXIT_FAILURE );
    } // try
    srand( seed );

    double rv = 0.0;
    int ev1 = 0, ev2 = 0, ev3 = 0;
    int rc = 0, ec1 = 0, ec2 = 0, ec3 = 0;
    variant<double, Er1, Er2, Er3> ret;

    for ( int i = 0; i < times; i += 1 ) {
        ret = rtn3( i );
        // analyse error
        if ( holds_alternative<double>(ret) ) {
            rv += get<double>(ret); rc += 1; 
        } else if ( holds_alternative<Er1>(ret) ) {
            ev1 += get<Er1>(ret).code; ec1 += 1;
        } else if ( holds_alternative<Er2>(ret) ) {
            ev2 += get<Er2>(ret).code; ec2 += 1;
        } else {
            ev3 += get<Er3>(ret).code; ec3 += 1;
        } // if
    } // for
    cout << "normal result " << rv << " exception results " << ev1 << ' ' << ev2 << ' ' << ev3 << endl;
    cout << "calls "  << rc << " exceptions " << ec1 << ' ' << ec2 << ' ' << ec3 << endl;
}