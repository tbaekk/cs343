#ifndef __Q1TALLYVOTES_H__
#define __Q1TALLYVOTES_H__

_Monitor Printer;

#if defined( MC )                   // mutex/condition solution
class TallyVotes {
    
#elif defined( SEM )                // semaphore solution
class TallyVotes {
    
#elif defined( BAR )                // barrier solution
#include <uBarrier.h>
_Cormonitor TallyVotes : public uBarrier {
#else
    #error unsupported voter type
#endif
  public:                            // common interface
    _Event Failed {};
    TallyVotes( unsigned int voters, unsigned int group, Printer & printer );
    struct Ballot { unsigned int picture, statue, giftshop; };
    enum Tour { Picture = 'p', Statue = 's', GiftShop = 'g' };
    Tour vote( unsigned int id, Ballot ballot );
    void done();
  private:
#if defined ( MC )

#elif defined ( SEM )

#elif defined ( BAR )
    uBaseTask *lastVoter;
    void last();
#endif
    // common declarations
    struct Ballot total = { 0, 0, 0 };
    unsigned int voters;
    unsigned int group;
    unsigned int numAvailVoters;
    Printer &printer;
    Tour tour;
    void countVotes ( Ballot ballot ) {
        total.picture  += ballot.picture;
        total.statue   += ballot.statue;
        total.giftshop += ballot.giftshop;
    }
    Tour bestVote() {
        Tour state = Tour::Picture;
        if (total.picture > total.giftshop) {
            if (total.picture < total.statue) {
                state = Tour::Statue;
            } // if
        } else if (total.picture == total.giftshop) {
            if (total.picture < total.statue) {
                state = Tour::Statue;
            } else {
                state = Tour::GiftShop;
            } // if
        } else {
            if (total.statue > total.giftshop) {
                state = Tour::Statue;
            } else {
                state = Tour::GiftShop;
            } // if
        } // if
        return state;
    }
};

#endif