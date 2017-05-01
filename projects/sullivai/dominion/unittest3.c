// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// unittest3.c
// Unit tests for buyCard() function in dominion.c
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

    memset(&G,'\0',sizeof(struct gameState));
    r = initializeGame(numPlayer,k,seed,&G);
    assert(!r);

    printf("\n\n#####################################################\n");
    printf("##             TESTING buyCards():                 ##\n");
    printf("#####################################################\n");

    // Test 1: not enough buys
    printf("Test 1: not enough buys\n");

    G.numBuys = 0;                  // set buys to 0
    G.supplyCount[estate] = 1;      // ensure there is a card
    G.coins = getCost(estate);      // ensure player has sufficient coin for the card
    tmp = G;                        // save current info
    result = buyCard(estate,&G);
    // buyCard returns -1
    sprintf(msg,"Not enough buys.");
    ASSERT2(result == -1, msg);
    // numBuys unchanged
    sprintf(msg,"Buys unchanged.");
    ASSERT2(G.numBuys == tmp.numBuys, msg);
    // supply unchanged
    sprintf(msg,"Supply unchanged.");
    ASSERT2(G.supplyCount[estate] == tmp.supplyCount[estate], msg);
    // coins unchanged
    sprintf(msg,"Coins unchanged.");
    ASSERT2(G.coins == tmp.coins, msg);



    // Test 2: not enough cards
    printf("Test 2: not enough cards\n");
    G.numBuys = 1;                  // ensure there are enough buys
    G.supplyCount[estate] = 0;      // set card supply to 0
    G.coins = getCost(estate);      // ensure player has sufficient coin for the card
    tmp = G;                        // save current info
    result = buyCard(estate,&G);
    // buyCard returns -1
    sprintf(msg,"Not enough cards.");
    ASSERT2(result == -1, msg);
    // numBuys unchanged
    sprintf(msg,"Buys unchanged.");
    ASSERT2(G.numBuys == tmp.numBuys, msg);
    // supply unchanged
    sprintf(msg,"Supply unchanged.");
    ASSERT2(G.supplyCount[estate] == tmp.supplyCount[estate], msg);
    // coins unchanged
    sprintf(msg,"Coins unchanged.");
    ASSERT2(G.coins == tmp.coins, msg);


    // Test 3: not enough dosh
    printf("Test 3: not enough coins\n");
    G.numBuys = 1;                  // ensure there are enough buys
    G.supplyCount[estate] = 1;      // ensure there are enough cards
    G.coins = 0;                    // set player money to 0
    tmp = G;                        // save current info
    result = buyCard(estate,&G);
    // buyCard returns -1
    sprintf(msg,"Not enough coins.");
    ASSERT2(result == -1, msg);
    // numBuys unchanged
    sprintf(msg,"Buys unchanged.");
    ASSERT2(G.numBuys == tmp.numBuys, msg);
    // supply unchanged
    sprintf(msg,"Supply unchanged.");
    ASSERT2(G.supplyCount[estate] == tmp.supplyCount[estate], msg);
    // coins unchanged
    sprintf(msg,"Coins unchanged.");
    ASSERT2(G.coins == tmp.coins, msg);


    // Test 4: buy card, make sure everything is updated correctly
    printf("Test 4: successful buy\n");
    G.numBuys = 1;                  // ensure there are enough buys
    G.supplyCount[estate] = 1;      // ensure there are enough cards
    G.coins = getCost(estate);      // ensure there is enough money
    G.discardCount[G.whoseTurn] = 0;  // set discard pile to zero
    tmp = G;                        // save current info
    result = buyCard(estate,&G);

    // return 0
    sprintf(msg,"Buy successful.");
    ASSERT2(!result, msg);

    // phase was 0, now == 1
    sprintf(msg,"Phase changed.");
    ASSERT2(G.phase == 1, msg);

    // coins == coins-cost
    sprintf(msg,"Cost applied.");
    ASSERT2(G.coins == 0, msg);

    // buys == buys - 1
    sprintf(msg,"Buys updated.");
    ASSERT2(G.numBuys == 0, msg);

    // supply[card] = supply[card]-1
    sprintf(msg,"Card supply updated.");
    ASSERT2(G.supplyCount[estate] == 0, msg);

    // discard[card] == discard[card]+1
    sprintf(msg,"Discard pile updated.");
    ASSERT2(G.discardCount[G.whoseTurn] == 1, msg);

    // card is in discard pile
    sprintf(msg,"Discard pile contains card.");
    ASSERT2(G.discard[G.whoseTurn][G.discardCount[G.whoseTurn]-1] == estate,msg);


    return 0;
}
