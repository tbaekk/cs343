#ifndef __Q2STATE_H__
#define __Q2STATE_H__

#include "q2tallyVotes.h"
#include "q2voter.h"

class State {
  Voter::States state;
  TallyVotes::Tour tour;
  TallyVotes::Ballot ballot;
  unsigned int numBlocked;
public:
  State( Voter::States state ); // S, b, C, X. T
  State( Voter::States state, TallyVotes::Tour tour ); // F t
  State( Voter::States state, TallyVotes::Ballot ballot ); // V
  State( Voter::States state, unsigned int numBlocked ); // B, U
  Voter::States getState();
  TallyVotes::Tour getTour();
  TallyVotes::Ballot getBallot();
  unsigned int getNumBlocked();
};

#endif