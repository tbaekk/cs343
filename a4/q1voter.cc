#include "q1voter.h"
#include "q1tallyVotes.h"
#include "MPRNG.h"

using namespace std;

Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer )
    :  id(id), nvotes(nvotes), tallier(&voteTallier), printer(&printer) {}

Voter::main() {
    yield( mprng( 19 ) );                                                   // Yield a random number of times

    for (int i = 0; i < nvotes; i++) {
        Voter::printer->print( id, Voter::States::Start );                  // Print start message

        yield( mprng(4) );                                                  // Yield a random number of times

        TallyVotes::Ballot ballot = Voter::cast();
        TallyVotes::Tour tour = Voter::tallier->vote( id, ballot );         // Vote

        yield( mprng(4) );                                                  // Yield a random number of times

        Voter::printer->print( id, Voter::States::Finished, tour );         // Print finish message
    }
    TallyVotes::done();
}