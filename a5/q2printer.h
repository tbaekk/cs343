#ifndef __Q1PRINTER_H__
#define __Q1PRINTER_H__

#include "q1tallyVotes.h"
#include "q1voter.h"

_Monitor Printer {
    unsigned int voters;
    char *buffer;
    void flush();
    void print();
    bool isExist( unsigned int id );
  public:
    Printer( unsigned int voters );
    ~Printer();
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot ballot );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif