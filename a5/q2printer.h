#ifndef __Q2PRINTER_H__
#define __Q2PRINTER_H__

#include <string>
#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2state.h"

_Monitor Printer {
    unsigned int voters;
    State **buffer; // holds internal representations for state of all the voters
    std::string prettyPrint(State *s);
    void flush(); // flush contents of buffer to stdout
  public:
    Printer( unsigned int voters );
    ~Printer();
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot ballot );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif