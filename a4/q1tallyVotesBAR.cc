#include "q1tallyVotes.h"
#include "q1printer.h"
#include "q1voter.h"

using namespace std;

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer )
    : uBarrier(group), voters(voters), group(group), numAvailVoters(voters), printer(printer) {}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
    if ( numAvailVoters < group ) {
        uBarrier::block();
        _Throw Failed();
    } // if

    countVotes( ballot );
#if defined ( OUTPUT ) 
    printer.print( id, Voter::Vote, ballot );
#endif

    if ( uBarrier::waiters() + 1 < group ) {
#if defined ( OUTPUT ) 
        printer.print( id, Voter::Block, uBarrier::waiters() + 1 );
#endif
    } // if
    
    uBarrier::block();

    if ( numAvailVoters < group ) {
        _Throw Failed();
    } // if

    if ( lastVoter == &uThisTask() ) {
        tour = bestVote();
        total = { 0, 0, 0 };
#if defined ( OUTPUT ) 
        printer.print( id, Voter::Complete );
#endif
    } // if

    return tour;
} // TallyVotes::vote

void TallyVotes::last() {
    lastVoter = &uThisTask();
} // TallyVotes::last

void TallyVotes::done() {
    numAvailVoters--;
    if ( numAvailVoters < group ) {
        uBarrier::block();
    }
} // TallyVotes::done