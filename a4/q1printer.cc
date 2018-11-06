#include <iostream>
#include <string>
#include "q1printer.h"

using namespace std;

Printer::Printer( unsigned int voters ) : voters(voters) {
    buffer = new char[ 8 * voters ];                                    // Printer buffer, which consists of 8 char per voter
    flush();
    string delim = "", star = "*******";
#if defined ( OUTPUT )
    for ( unsigned int i = 0; i < voters; ++i ) {                       // Print the header info
        cout << "V" << i << '\t';
        delim += star + '\t';
    } // for
    cout << endl;
    cout << delim << endl;                                              // Print the separating stars
#endif
} // Printer::Printer

Printer::~Printer() {
    for ( unsigned int i = 0; i < Printer::voters; ++i ) {              // Check if there are remaining info yet to be printed before we delete them
        if ( Printer::isExist( i ) ) {
            print();
            break;
        } // if
    } // for
    delete buffer;
#if defined ( OUTPUT )
    cout << "*****************" << endl;                                // Print the ending info
    cout << "All tours started" << endl;
#endif
} // Printer::~Printer

void Printer::flush() {                                                 // Helper that flushes the buffer
    int len = 8 * voters;
    for ( int i = 0; i < len; ++i ) {
        if ( i % 8 == 0) {
            buffer[i] = '\t';                                           // Set the first char of the buffer for each voter to be \t
        } else {
            buffer[i] = NULL;                                           // Set all other chars to be NULL
        } // if
    } // for
} // Printer::flush

void Printer::print() {                                                 // Helper that print the buffer on screen
    for ( unsigned int i = 0; i < 8 * Printer::voters; ++i ) {
        if ( buffer[i] == NULL ) continue;
        cout << buffer[i];
    } // for
    cout << endl;
    flush();                                                            // Printing done, flush the buffer
} // Printer::print


bool Printer::isExist( unsigned int id ) {                              // Helper that check if there are info stored in the buffer of the id-th voter
    return buffer[ 8 * id ] != '\t';
} // Printer::isExist

void Printer::print( unsigned int id, Voter::States state ) {
    if ( isExist( id ) ) {
        print();
    } // if
    unsigned int i = 8 * id;
    buffer[i++] = state;
    buffer[i++] = '\t';
} // Printer::print

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour tour ) {
    if ( isExist( id ) ) {
        print();
    } // if
    unsigned int i = 8 * id;
    buffer[i++] = state;
    buffer[i++] = ' ';
    buffer[i++] = tour;
    buffer[i++] = '\t';
} // Printer::print

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Ballot ballot ) {
    if ( isExist( id ) ) {
        print();
    } // if
    unsigned int i = 8 * id;
    buffer[i++] = state;
    buffer[i++] = ' ';
    buffer[i++] = ballot.picture + 48;
    buffer[i++] = ',';
    buffer[i++] = ballot.statue + 48;
    buffer[i++] = ',';
    buffer[i++] = ballot.giftshop + 48;
    buffer[i++] = '\t';
} // Printer::print

void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked ) {
    if ( isExist( id ) ) {
        print();
    } // if
    unsigned int i = 8 * id;
    buffer[i++] = state;
    buffer[i++] = ' ';
    string tmp = to_string( numBlocked );
    for ( ;; ) {
        char c = tmp[0];
      if ( tmp.empty() ) break;
        buffer[ i++ ] = c;
        tmp = tmp.substr( 1 );
    }
    buffer[ i++ ] = '\t';
} // Printer::print
