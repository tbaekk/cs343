#ifndef __Q1VOTER_H__
#define __Q1VOTER_H__

#include "MPRNG.h"
#include "q1tallyVotes.h"

_Monitor Printer;
extern MPRNG mprng;

_Task Voter {
    unsigned int id;
    unsigned int nvotes;
    TallyVotes &voteTallier;
    Printer &printer;
    TallyVotes::Ballot cast();
    void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Barging = 'b',
                   Complete = 'C', Finished = 'F', Failed = 'X', Terminated = 'T' };
    Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer );
};

#endif