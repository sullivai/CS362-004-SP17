// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// cardtest2.c
// Unit tests for adventurer card
// Structure of code is based on cardtest4.c provided in Assignment 3 Assistance 
// in course materials.


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
// http://stackoverflow.com/a/12989329
#define ASSERT2(xy,MSG) do {\
!(xy) ? printf("     TEST FAILED: %s\n",MSG) : printf("TEST PASSED: %s\n",MSG);\
} while(0)

// ---------------------test do or do not have to shuffle to look for more cards
// reveal n cards from deck til 2 treasure found
// ----------------------test 0,1,2,3 treasure in deck
// +2 treasure in hand if 2 treasure found
// +1 treasure if only 1 treasure in deck
// 0 treasure if no treasure in deck <---- test 
// ----------------------
// no change to others state
// no change to supply
//

int main() {
    char msg[1024];
    int newCards = 0;
    int discarded = 1;
    //int xtraCoins = 0;
    int shuffledCards = 0;
    int extraBuys = 0;

    int i,j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: no treasures in deck - gain nothing --------------
	printf("TEST 1: no treasures in deck - gain nothing\n");
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    thisPlayer = 0;
    newCards = 0;   
    handpos = 0;
    extraBuys = 0;
    //xtraCoins = 0;

    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = adventurer;
    // make sure there are no treasures in hand
    for (i = 1; i < G.handCount[thisPlayer]; i++){    
        G.hand[thisPlayer][i] = estate;
    }
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    // supply piles
    for (j = 0; j <= treasure_map; j++){
        sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]);
        ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
    }
    // hand count
    sprintf(msg,"hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
    ASSERT2(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded, msg);
    // deck count
    sprintf(msg,"deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    ASSERT2(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, msg);
    // discard count
    sprintf(msg,"discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+discarded);
    ASSERT2(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]+discarded, msg);
    // buys
    sprintf(msg,"buys = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    ASSERT2(testG.numBuys == G.numBuys + extraBuys, msg);



	// ----------- TEST 2: only 1 treasure in deck - +1 in hand  --------------
	printf("TEST 2: 1 treasure in deck - +1 in hand\n");
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    thisPlayer = 0;
    newCards = 1;   
    handpos = 0;
    extraBuys = 0;
    //xtraCoins = 1;

    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = adventurer;
    G.hand[thisPlayer][handpos+1] = copper;
    // make sure there is only one treasure in hand
    for (i = 2; i < G.handCount[thisPlayer]; i++){    
        G.hand[thisPlayer][i] = estate;
    }
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    // supply piles
    for (j = 0; j <= treasure_map; j++){
        sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]);
        ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
    }
    // hand count
    sprintf(msg,"hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    ASSERT2(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, msg);
    // deck count
    sprintf(msg,"deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    ASSERT2(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, msg);
    // discard count
    sprintf(msg,"discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+discarded);
    ASSERT2(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]+discarded, msg);
    // buys
    sprintf(msg,"buys = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    ASSERT2(testG.numBuys == G.numBuys + extraBuys, msg);




	// ----------- TEST 3: 2 treasures in deck - +2 in hand  --------------
	printf("TEST 3: 2 treasures in deck - +2 in hand\n");
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    thisPlayer = 0;
    newCards = 2;   
    handpos = 0;
    extraBuys = 0;
    //xtraCoins = 2;

    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = adventurer;
    G.hand[thisPlayer][handpos+1] = copper;
    G.hand[thisPlayer][handpos+2] = copper;
    // make sure there is only one treasure in hand
    for (i = 3; i < G.handCount[thisPlayer]; i++){    
        G.hand[thisPlayer][i] = estate;
    }
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    // supply piles
    for (j = 0; j <= treasure_map; j++){
        sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]);
        ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
    }
    // hand count
    sprintf(msg,"hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    ASSERT2(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, msg);
    // deck count
    sprintf(msg,"deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    ASSERT2(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, msg);
    // discard count
    sprintf(msg,"discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+discarded);
    ASSERT2(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]+discarded, msg);
    // buys
    sprintf(msg,"buys = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    ASSERT2(testG.numBuys == G.numBuys + extraBuys, msg);
    





	return 0;
}


