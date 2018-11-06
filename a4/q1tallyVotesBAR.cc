#include "q1tallyVotes.h"
#include "q1printer.h"
#include "q1voter.h"

using namespace std;

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer )
    : uBarrier(group), voters(voters), group(group), numAvailVoters(voters), printer(printer) {}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
    if ( numAvailVoters < group ) {
        _Throw Failed();
    } 

#if defined ( OUTPUT ) 
    printer.print( id, Voter::Vote, ballot );
#endif

    countVotes( ballot );

#if defined ( OUTPUT )
    printer.print( id, Voter::Block, uBarrier::waiters() + 1 );
#endif
    uBarrier::block();
#if defined ( OUTPUT )
    printer.print( id, Voter::Unblock, uBarrier::waiters() );
#endif
    if ( numAvailVoters < group ) {
        _Throw Failed();
    } 

    if ( lastVoter == &uThisTask() ) {
#if defined ( OUTPUT )        
        printer.print( id, Voter::Complete );
#endif
    }

    total = { 0, 0, 0 };

    return bestVote();
}

void TallyVotes::last() {
    lastVoter = &uThisTask();
}

void TallyVotes::done() {
    numAvailVoters--;
    if ( numAvailVoters < group ) {
        uBarrier::block();
    }
}