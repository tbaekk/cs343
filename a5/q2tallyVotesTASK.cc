#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"

using namespace std;

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer )
    : failed(false), voters(voters), group(group), numAvailVoters(voters), numWaitVoters(0), printer(printer) {}

void TallyVotes::main() {
    for (;;) {
        try {
            _Accept( ~TallyVotes ) {
                break;
            } or _Accept( vote ) {
                countVotes( ballot );
            #if defined ( OUTPUT )
                printer.print( id, Voter::Vote, ballot );

                printer.print( id, Voter::Block, numWaitVoters + 1 );
            #endif
                numWaitVoters++;

                if ( numWaitVoters >= group ) {                                     // Check if this voter is the last one to form a group
                #if defined ( OUTPUT )
                    printer.print( id, Voter::Complete );                           // If yes, print the complete message
                #endif
                    tour = bestVote();
                    resetVotes();                                                   // Reset voting result for the next group, if this voter is the last one in a group

                    while ( !bench.empty() ) {
                    #if defined ( OUTPUT )
                        printer.print( bench.front(), Voter::Unblock, numWaitVoters - 1 );
                    #endif
                        numWaitVoters--;
                        bench.signalBlock();
                    } // while
                } // if
            } or _Accept( done ) {
                if ( numAvailVoters < group ) {
                    failed = true;

                    while ( !bench.empty() ) {
                        bench.signalBlock();
                    } // while
                } // if
            } // _Accept
        } catch ( uMutexFailure::RendezvousFailure & ) {}
    } // for
} // TallyVotes::main

TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
    TallyVotes::id = id;
    TallyVotes::ballot = ballot;

    bench.wait( id );

    if ( failed ) {
        _Throw Failed();
    }

    return tour;
} // TallyVotes::vote

void TallyVotes::done() {
    numAvailVoters--;
} // TallyVotes::done