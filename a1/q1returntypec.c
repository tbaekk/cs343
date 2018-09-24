#include <stdio.h>
#include <stdlib.h>                                     // access: rand, srand
#include <string.h>                                     // access: strcmp
#include <unistd.h>                                     // access: getpid

struct Er1 { short int code; };
struct Er2 { int code; };
struct Er3 { long int code; };

enum TypeTag { RV_ACTIVE, ER1_ACTIVE, ER2_ACTIVE, ER3_ACTIVE };
struct ErUnion {
    enum TypeTag tag;
    union {
        double rv;
        struct Er1 er1;
        struct Er2 er2;
        struct Er3 er3; 
    };
};

int eperiod = 10000;                                    // error period

struct ErUnion rtn1( double i ) {
    struct ErUnion u;
    if ( rand() % eperiod == 0 ) {
        u.er1 = (struct Er1){ (short int)rand() };
        u.tag = ER1_ACTIVE;
    } else {
        u.rv = i;
        u.tag = RV_ACTIVE;
    } // if
    return u;
}
struct ErUnion rtn2( double i ) {
    struct ErUnion u;
    if ( rand() % eperiod == 0 ) {
        u.er2 = (struct Er2){ rand() };
        u.tag = ER2_ACTIVE;
    } else {
        u = rtn1( i );
        if ( u.tag == RV_ACTIVE ) {
            u.rv += i;
        } // if
    } // if
    return u;
}
struct ErUnion rtn3( double i ) {
    struct ErUnion u;
    if ( rand() % eperiod == 0 ) {
        u.er3 = (struct Er3){ rand() };
        u.tag = ER3_ACTIVE;
    } else {
        u = rtn2( i );
        if ( u.tag == RV_ACTIVE ) {
            u.rv += i;
        } // if
    } // if
    return u;
}
int main( int argc, char * argv[] ) {
    int times = 100000000, seed = getpid();             // default values
    switch ( argc ) {
        case 4: if ( strcmp( argv[3], "d" ) != 0 ) {  // default ?
            seed = atoi( argv[3] ); if ( seed <= 0 ) goto ExitProgram;
        } // if
        case 3: if ( strcmp( argv[2], "d" ) != 0 ) {  // default ?
            eperiod = atoi( argv[2] ); if ( eperiod <= 0 ) goto ExitProgram;
        } // if
        case 2: if ( strcmp( argv[1], "d" ) != 0 ) {  // default ?
            times = atoi( argv[1] ); if ( times <= 0 ) goto ExitProgram;
        } // if
        case 1: goto Main;                                // use all defaults
        default: goto ExitProgram;
    } // switch
ExitProgram:
    fprintf(stderr, "Usage: %s [ times > 0 | d [ eperiod > 0 | d [ seed > 0 ] ] ]\n", argv[0]);
    exit( EXIT_FAILURE );
Main:
    srand( seed );

    double rv = 0.0;
    int ev1 = 0, ev2 = 0, ev3 = 0;
    int rc = 0, ec1 = 0, ec2 = 0, ec3 = 0;
    struct ErUnion ret;

    for ( int i = 0; i < times; i += 1 ) {
        ret = rtn3( i );
        // analyse error
        if ( ret.tag == RV_ACTIVE ) {
            rv += ret.rv; rc += 1; 
        } else if ( ret.tag == ER1_ACTIVE ) {
            ev1 += ret.er1.code; ec1 += 1;
        } else if ( ret.tag == ER2_ACTIVE ) {
            ev2 += ret.er2.code; ec2 += 1;
        } else {
            ev3 += ret.er3.code; ec3 += 1;
        } // if
    } // for
    printf("normal result %.5g exception results %d %d %d\n", rv, ev1, ev2, ev3);
    printf("calls %d exceptions %d %d %d\n", rc, ec1, ec2, ec3);
}