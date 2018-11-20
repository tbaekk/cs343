#include "q2state.h"

State::State( Voter::States state ) : state(state) {}

State::State( Voter::States state, TallyVotes::Tour tour ) : state(state), tour(tour) {}

State::State( Voter::States state, TallyVotes::Ballot ballot ) : state(state), ballot(ballot) {}

State::State( Voter::States state, unsigned int numBlocked ) : state(state), numBlocked(numBlocked) {}

Voter::States State::getState() {
    return state;
}

TallyVotes::Tour State::getTour() {
    return tour;
}

TallyVotes::Ballot State::getBallot() {
    return ballot;
}

unsigned int State::getNumBlocked() {
    return numBlocked;
}