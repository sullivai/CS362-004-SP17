// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// unittest1.c
// Unit tests for scoreFor() function in dominion.c
// Structure of code is based on testUpdateCoins.c provided in Assignment 3 Assistance 2
// in course materials.
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
// https://bytes.com/topic/c/answers/524316-help-writing-my-own-assert
#define ASSERT(xy,MSG) do {\
if(!(xy)){\
printf("TEST FAILED: %s\n",MSG);\
} \
}while(0)
*/

// http://stackoverflow.com/a/12989329
#define ASSERT2(xy,MSG) do {\
!(xy) ? printf("     TEST FAILED: %s\n",MSG) : printf("TEST PASSED: %s\n",MSG);\
} while(0)



int main() {
    char msg[1024] = {'\0'};
    int i, p, r, handCount, discardCount,  deckCount, totalCards;
    // Some information needed to initialize game state
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    // Set up full "decks" of each kind of card that is used in scoring
    int curses[MAX_HAND];
    int estates[MAX_HAND];
    int duchies[MAX_HAND];
    int provinces[MAX_HAND];
    int great_halls[MAX_HAND];
    int gardenses[MAX_HAND];

    for (i = 0; i < maxHandCount; i++){
        curses[i] = curse;
        estates[i] = estate;
        duchies[i] = duchy;
        provinces[i] = province;
        great_halls[i] = great_hall;
        gardenses[i] = gardens;
    }

    printf("\n\n#####################################################\n");
    printf("##             TESTING scoreFor():                 ##\n");
    printf("#####################################################\n");

    p = 0;  // This player

    // Set up game    
    memset(&G,'\0',sizeof(struct gameState));
    r = initializeGame(numPlayer,k,seed,&G);
    assert(!r);

    // Loop to test 0, 1, and more than one of cards
    // Go up to 2 digits total cards to register a score on gardens
    for (handCount = 0; handCount < maxHandCount; handCount++){
    for (discardCount = 0; discardCount < maxHandCount; discardCount++){
    for (deckCount = 0; deckCount < maxHandCount; deckCount++){
        // Set hand, discard, and deck to be 0 or some # of cards
        G.handCount[p] = handCount;
        G.discardCount[p] = discardCount;
        G.deckCount[p] = deckCount;
        totalCards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    
        // Test curse
        memcpy(G.hand[p],curses,sizeof(int)*G.handCount[p]);        
        memcpy(G.discard[p],curses,sizeof(int)*G.discardCount[p]);
        memcpy(G.deck[p],curses,sizeof(int)*G.deckCount[p]);
        sprintf(msg,"CURSE with %d in hand, %d in discard, %d in deck. Score: %d Expected: %d", handCount, discardCount, deckCount, scoreFor(p,&G), (-1 * totalCards));
        ASSERT2(scoreFor(p,&G) == (-1 * totalCards),msg);
        
        // Test estate
        memcpy(G.hand[p],estates,sizeof(int)*G.handCount[p]);
        memcpy(G.discard[p],estates,sizeof(int)*G.discardCount[p]);
        memcpy(G.deck[p],estates,sizeof(int)*G.deckCount[p]);
        sprintf(msg,"ESTATE with %d in hand, %d in discard, %d in deck. Score: %d Expected: %d", handCount, discardCount, deckCount, scoreFor(p,&G), (1 * totalCards));
        ASSERT2(scoreFor(p,&G) == (1 * totalCards),msg);
    
        // Test duchy
        memcpy(G.hand[p],duchies,sizeof(int)*G.handCount[p]);
        memcpy(G.discard[p],duchies,sizeof(int)*G.discardCount[p]);
        memcpy(G.deck[p],duchies,sizeof(int)*G.deckCount[p]);
        sprintf(msg,"DUCHY with %d in hand, %d in discard, %d in deck. Score: %d Expected: %d", handCount, discardCount, deckCount, scoreFor(p,&G), (3 * totalCards));
        ASSERT2(scoreFor(p,&G) == (3 * totalCards),msg);

        // Test province
        memcpy(G.hand[p],provinces,sizeof(int)*G.handCount[p]);
        memcpy(G.discard[p],provinces,sizeof(int)*G.discardCount[p]);
        memcpy(G.deck[p],provinces,sizeof(int)*G.deckCount[p]);
        sprintf(msg,"PROVINCE with %d in hand, %d in discard, %d in deck. Score: %d Expected: %d", handCount, discardCount, deckCount, scoreFor(p,&G), (6 * totalCards));
        ASSERT2(scoreFor(p,&G) == (6 * totalCards),msg);

        // Test great_hall
        memcpy(G.hand[p],great_halls,sizeof(int)*G.handCount[p]);
        memcpy(G.discard[p],great_halls,sizeof(int)*G.discardCount[p]);
        memcpy(G.deck[p],great_halls,sizeof(int)*G.deckCount[p]);
        sprintf(msg,"GREAT_HALL with %d in hand, %d in discard, %d in deck. Score: %d Expected: %d", handCount, discardCount, deckCount, scoreFor(p,&G), (1 * totalCards));
        ASSERT2(scoreFor(p,&G) == (totalCards),msg);

        // Test gardens
        memcpy(G.hand[p],gardenses,sizeof(int)*G.handCount[p]);
        memcpy(G.discard[p],gardenses,sizeof(int)*G.discardCount[p]);
        memcpy(G.deck[p],gardenses,sizeof(int)*G.deckCount[p]);
        sprintf(msg,"GARDEN with %d in hand, %d in discard, %d in deck. Score: %d Expected: %d", handCount, discardCount, deckCount, scoreFor(p,&G), (totalCards/10));
        ASSERT2(scoreFor(p,&G) == (totalCards/10),msg);   
    }
    }
    }

    //printf("All tests passed.\n");
    return 0;
}
