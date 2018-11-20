#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"

using namespace std;

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer )
    : tickets(0), curTicket(group), voters(voters), group(group), numAvailVoters(voters), numWaitVoters(0), printer(printer) {}

void TallyVotes::wait() {
    bench.wait();                            // wait until signalled
    while ( rand() % 2 == 0 ) {              // multiple bargers allowed
        try {
            _Accept( vote, done ) {          // accept barging callers
            } _Else {                        // do not wait if no callers
            } // _Accept
        } catch( uMutexFailure::RendezvousFailure & ) {}
    } // while
} // TallyVotes::wait

void TallyVotes::signalAll() {               // also useful
    while ( ! bench.empty() ) bench.signal();// drain the condition
} // TallyVotes::signalAll

TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
    if ( numAvailVoters < group ) {
        _Throw Failed();
    } // if

    unsigned int ticket = tickets;
    tickets++;
    while ( ticket >= curTicket ) {
#if defined ( OUTPUT )
        printer.print( id, Voter::Barging );
#endif
        wait();
    }

    countVotes( ballot );
#if defined ( OUTPUT )
    printer.print( id, Voter::Vote, ballot ); 
#endif
    numWaitVoters++;
    if ( numWaitVoters < group ) {                                      // Check if this voter is the last one to form a group
#if defined ( OUTPUT )
        printer.print( id, Voter::Block, numWaitVoters );               // If NOT, wait for more voters coming
#endif
        wait();
#if defined ( OUTPUT )
        printer.print( id, Voter::Unblock, numWaitVoters - 1 );
#endif
    } else {
#if defined ( OUTPUT )
        printer.print( id, Voter::Complete );                           // If yes, print the complete message
#endif
        tour = bestVote();
        resetVotes();                                                   // Reset voting result for the next group, if this voter is the last one in a group
        signalAll();     
    } // if

    if ( numAvailVoters < group ) {
        _Throw Failed();
    } // if

    numWaitVoters--;
    if ( numWaitVoters == 0 ) {
        curTicket += group;
        signalAll();
    } // if

    return tour;
} // TallyVotes::vote

void TallyVotes::done() {
    numAvailVoters--;
    if ( numAvailVoters < group ) {
        signalAll();
    }
} // TallyVotes::done