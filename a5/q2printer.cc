#include <iostream>
#include <string>
#include "q2printer.h"

using namespace std;

Printer::Printer( unsigned int voters ) : voters(voters) {
    Printer::voters = voters;
    buffer = new State*[voters];                                    // 1 buffer slot for each voter
    for (unsigned int i = 0; i < voters; ++i) {
        buffer[i] = nullptr;                                        // Init nullptr
    }

    // output header
#if defined ( OUTPUT )
    cout << "V0";
    for (unsigned int i = 1; i < voters; ++i) {
        cout << "\tV" << i;
    }
    cout << endl;

    cout << "*******";
    for (unsigned int i = 1; i < voters; ++i) {
        cout << "\t*******";
    }
    cout << endl;
#endif
} // Printer::Printer

Printer::~Printer() {
#if defined ( OUTPUT )
    flush();
#endif
    for ( unsigned int i = 0; i < voters; ++i ) {
        delete buffer[i];
    } // for
    delete[] buffer;
#if defined ( OUTPUT )
    cout << "*****************" << endl;
    cout << "All tours started" << endl;
#endif
} // Printer::~Printer


/*********** flush ***********
    Purpose: Flushes the buffer.


    Returns: None.


    Errors: If buffer is empty, could cause index out of bounds.
************************************/

string Printer::prettyPrint(State *s) {
    Voter::States state       = s->getState();
    TallyVotes::Tour tour     = s->getTour();
    TallyVotes::Ballot ballot = s->getBallot();
    unsigned int numBlocked   = s->getNumBlocked();
    switch (state) {
        case Voter::Start:
        case Voter::Barging:
        case Voter::Complete:
        case Voter::Failed:
        case Voter::Terminated:
            return string(1, state);
        case Voter::Finished:
            return string(1, state) + " " + string(1, tour);
        case Voter::Vote:
            return string(1, state) + " " + to_string(ballot.picture) + "," + to_string(ballot.statue) + "," + to_string(ballot.giftshop);
        case Voter::Block:
        case Voter::Unblock:
            return string(1, state) + " " + to_string(numBlocked);
        default:
            throw; // invalid state
  }
}

void Printer::flush() {
    unsigned int highest;
    for ( unsigned int i = voters - 1; i >= 0; --i ) {                  // Find index to stop printing
        if (buffer[i] != nullptr) {
            highest = i;
            break;
        } // if
    } // for

    if (buffer[0] != nullptr) {
        string output = prettyPrint(buffer[0]);
        cout << output;
                                                                        // Clear buffer and set to nullptr
        delete buffer[0];
        buffer[0] = nullptr;
    } // if

    for ( unsigned int i = 1; i <= highest; ++i ) {                     // Output all voters in the buffer
        if (buffer[i] != nullptr) {
            cout << "\t" << prettyPrint(buffer[i]);

            delete buffer[i];                                           // Clear buffer and set to nullptr
            buffer[i] = nullptr;
        } else if (i != highest) {
            cout << "\t";
        } // if
    } // for
    cout << endl;
} // Printer::flush

void Printer::print( unsigned int id, Voter::States state ) {
    if (buffer[id] != nullptr) {
        flush();
    } // if
    buffer[id] = new State(state);
} // Printer::print

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour tour ) {
    if (buffer[id] != nullptr) {
        flush();
    } // if
    buffer[id] = new State(state, tour);
} // Printer::print

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Ballot ballot ) {
    if (buffer[id] != nullptr) {
        flush();
    } // if
    buffer[id] = new State(state, ballot);
} // Printer::print

void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked ) {
    if (buffer[id] != nullptr) {
        flush();
    } // if
    buffer[id] = new State(state, numBlocked);
} // Printer::print
