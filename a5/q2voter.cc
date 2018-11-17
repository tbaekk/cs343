#include "q2voter.h"
#include "q2printer.h"

using namespace std;

Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer )
    :  id(id), nvotes(nvotes), voteTallier(voteTallier), printer(printer) {}

TallyVotes::Ballot Voter::cast() {
    // O(1) random selection of 3 items without replacement using divide and conquer.
    static unsigned int voting[3][2][2] = { { {2,1}, {1,2} }, { {0,2}, {2,0} }, { {0,1}, {1,0} } };
    unsigned int picture = mprng( 2 ), statue = mprng( 1 );
    return (TallyVotes::Ballot){ picture, voting[picture][statue][0], voting[picture][statue][1] };
} // Voter::cast

void Voter::main() {
    yield( mprng( 19 ) );                                                   // Yield a random number of times

    try {
        for (unsigned int i = 0; i < nvotes; i++) {
            printer.print( id, Voter::Start );                              // Print start message
            
            yield( mprng(4) );                                              // Yield a random number of times

            TallyVotes::Ballot ballot = Voter::cast();
            TallyVotes::Tour tour = voteTallier.vote( id, ballot );         // Vote

            yield( mprng(4) );                                              // Yield a random number of times

            printer.print( id, Voter::Finished, tour );                     // Print finish message
        }
        voteTallier.done();

        printer.print( id, Voter::Terminated );
    } catch ( TallyVotes::Failed ) {
        printer.print( id, Voter::Failed );
    }
} // Voter::main
