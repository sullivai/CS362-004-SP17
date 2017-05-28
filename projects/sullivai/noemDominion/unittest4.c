// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// unittest4.c
// Unit tests for gainCard() function in dominion.c
// Structure of code is based on testUpdateCoins.c provided in Assignment 3 Assistance 2
// in course materials.
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// http://stackoverflow.com/a/12989329
#define ASSERT2(xy,MSG) do {\
!(xy) ? printf("     TEST FAILED: %s\n",MSG) : printf("TEST PASSED: %s\n",MSG);\
} while(0)



int main() {
    char msg[1024];
    int result; 
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState tmp;    

    printf("\n\n#####################################################\n");
    printf("##             TESTING gainCard():                 ##\n");
    printf("#####################################################\n");
    // Test 1: Card not available, do not gain
    memset(&G,'\0',sizeof(struct gameState));
    r = initializeGame(numPlayer,k,seed,&G);
    assert(!r);
    G.supplyCount[adventurer] = 0;  // make sure there's no card
    tmp = G;                        // save current info
    result = gainCard(adventurer,&G,0,G.whoseTurn);
    printf("Test 1: Card not available\n");
    // Return -1
    sprintf(msg,"Card not available.");
    ASSERT2(result == -1, msg);
    // No change to supply
    sprintf(msg,"Card supply count unchanged.");
    ASSERT2(G.supplyCount[adventurer] == tmp.supplyCount[adventurer], msg);
    // No change to player deck
    sprintf(msg,"Player deck count unchanged.");
    ASSERT2(G.deckCount[G.whoseTurn] == tmp.deckCount[tmp.whoseTurn], msg);
    // No change to player hand
    sprintf(msg,"Player hand count unchanged.");
    ASSERT2(G.handCount[G.whoseTurn] == tmp.handCount[tmp.whoseTurn], msg);
    // No change to player discard
    sprintf(msg,"Player discard count unchanged.");
    ASSERT2(G.discardCount[G.whoseTurn] == tmp.discardCount[G.whoseTurn], msg);

    // Test 2: Add card to deck
    memset(&G,'\0',sizeof(struct gameState));
    r = initializeGame(numPlayer,k,seed,&G);
    assert(!r);
    G.supplyCount[adventurer] = 1;  // make sure there's a card
    tmp = G;                        // save current info
    result = gainCard(adventurer,&G,1,G.whoseTurn);
    printf("\nTest 2: Add card to deck\n");
    // Supply - 1
    sprintf(msg,"Card supply adjusted.");
    ASSERT2(G.supplyCount[adventurer] == tmp.supplyCount[adventurer]-1, msg);
    // Deck + 1
    sprintf(msg,"Deck adjusted.");
    ASSERT2(G.deckCount[G.whoseTurn] == tmp.deckCount[tmp.whoseTurn]+1, msg);
    // No change to hand
    sprintf(msg,"Player hand count unchanged.");
    ASSERT2(G.handCount[G.whoseTurn] == tmp.handCount[tmp.whoseTurn], msg);
    // No change to discard
    sprintf(msg,"Player discard count unchanged.");
    ASSERT2(G.discardCount[G.whoseTurn] == tmp.discardCount[G.whoseTurn], msg);
    // Card is in player deck
    sprintf(msg,"Card is in deck.");
    ASSERT2(G.deck[G.whoseTurn][G.deckCount[G.whoseTurn]-1] == adventurer,msg);

    // Test 3: Add card to hand
    memset(&G,'\0',sizeof(struct gameState));
    r = initializeGame(numPlayer,k,seed,&G);
    assert(!r);
    G.supplyCount[adventurer] = 1;  // make sure there's a card
    tmp = G;                        // save current info
    result = gainCard(adventurer,&G,2,G.whoseTurn);
    printf("\nTest 3: Add card to hand\n");
    // Supply - 1
    sprintf(msg,"Card supply adjusted.");
    ASSERT2(G.supplyCount[adventurer] == tmp.supplyCount[adventurer]-1, msg);
    // No change to deck
    sprintf(msg,"Player deck count unchanged.");
    ASSERT2(G.deckCount[G.whoseTurn] == tmp.deckCount[tmp.whoseTurn], msg);
    // Hand + 1
    sprintf(msg,"Hand adjusted.");
    ASSERT2(G.handCount[G.whoseTurn] == tmp.handCount[tmp.whoseTurn]+1, msg);
    // No change to discard
    sprintf(msg,"Player discard count unchanged.");
    ASSERT2(G.discardCount[G.whoseTurn] == tmp.discardCount[G.whoseTurn], msg);
    // Card is in player hand
    sprintf(msg,"Card is in hand.");
    ASSERT2(G.hand[G.whoseTurn][G.handCount[G.whoseTurn]-1] == adventurer,msg);

    // Test 4: Add card to discard
    memset(&G,'\0',sizeof(struct gameState));
    r = initializeGame(numPlayer,k,seed,&G);
    assert(!r);
    G.supplyCount[adventurer] = 1;  // make sure there's a card
    tmp = G;                        // save current info
    result = gainCard(adventurer,&G,0,G.whoseTurn);
    printf("\nTest 4: Add card to discard\n");
    // Supply - 1
    sprintf(msg,"Card supply adjusted.");
    ASSERT2(G.supplyCount[adventurer] == tmp.supplyCount[adventurer]-1, msg);
    // No change to deck
    sprintf(msg,"Player deck count unchanged.");
    ASSERT2(G.deckCount[G.whoseTurn] == tmp.deckCount[tmp.whoseTurn], msg);
    // No change to hand
    sprintf(msg,"Player hand count unchanged.");
    ASSERT2(G.handCount[G.whoseTurn] == tmp.handCount[tmp.whoseTurn], msg);
    // Discard + 1
    sprintf(msg,"Discard adjusted.");
    ASSERT2(G.discardCount[G.whoseTurn] == tmp.discardCount[tmp.whoseTurn]+1, msg);
    // Card is in player discard pile
    sprintf(msg,"Card is in discard pile.");
    ASSERT2(G.discard[G.whoseTurn][G.discardCount[G.whoseTurn]-1] == adventurer,msg);

    return 0;
}
