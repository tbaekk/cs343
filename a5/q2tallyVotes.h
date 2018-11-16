#ifndef __Q2TALLYVOTES_H__
#define __Q2TALLYVOTES_H__

_Monitor Printer;

#if defined( EXT )                           // external scheduling monitor solution
_Monitor TallyVotes {

#elif defined( INT )                         // internal scheduling monitor solution
_Monitor TallyVotes {

#elif defined( INTB )                        // internal scheduling monitor solution with barging
_Monitor TallyVotes {
    
#elif defined( AUTO )                        // automatic-signal monitor solution
_Monitor TallyVotes {

#elif defined( TASK )                        // internal/external scheduling task solution
_Task TallyVotes {

#else
    #error unsupported voter type
#endif
  public:                                    // common interface
    _Event Failed {};
    TallyVotes( unsigned int voters, unsigned int group, Printer & printer );
    struct Ballot { unsigned int picture, statue, giftshop; };
    enum Tour { Picture = 'p', Statue = 's', GiftShop = 'g' };
    Tour vote( unsigned int id, Ballot ballot );
    void done();
  private:
#if defined( EXT )

#elif defined( INT )

#elif defined( INTB )
    uCondition bench;                        // only one condition variable (you may change the variable name)
    void wait();                             // barging version of wait
    void signalAll();                        // unblock all waiting tasks
#elif defined( AUTO )

#elif defined( TASK )

#endif
    // common declarations
    struct Ballot total = { 0, 0, 0 };
    unsigned int voters;
    unsigned int group;
    unsigned int numAvailVoters;
    unsigned int numWaitVoters;
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