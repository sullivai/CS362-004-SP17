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
/*

int main() {
    char msg[1024];
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int extraBuys = 0;

    int j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: play TESTCARD and check all values are updated correctly for player --------------
	printf("\nTEST 1: play %s - draw 3/discard 1 = +2 in hand, -3 in deck,+0 buys, +0 coins\n",TESTCARD);
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);

    thisPlayer = 0;
    newCards = 3;   // this player draws 3 cards
    handpos = 0;
    extraBuys = 0;

    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = smithy;    
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
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
    sprintf(msg,"discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    ASSERT2(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], msg);
    // played count
    sprintf(msg,"played count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + discarded);
    ASSERT2(testG.playedCardCount == G.playedCardCount + discarded, msg);
    // card in played pile
    sprintf(msg,"played card = %d, expected = %d", testG.playedCards[testG.playedCardCount-1], smithy);
    ASSERT2(testG.playedCards[testG.playedCardCount-1] == smithy, msg);
    // buys
    sprintf(msg,"buys = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    ASSERT2(testG.numBuys == G.numBuys + extraBuys, msg);
    // coins
    sprintf(msg,"coins = %d, expected = %d", testG.coins, G.coins + xtraCoins);
    ASSERT2(testG.coins == G.coins + xtraCoins, msg);


    // ---------------------test do or do not have to shuffle to look for more cards
    //
    //
    // reveal n cards from deck til 2 treasure found
    // ----------------------test 0,1,2,3 treasure in deck
    // +2 treasure in hand if 2 treasure found
    // +1 treasure if only 1 treasure in deck
    // 0 treasure if no treasure in deck <---- test 
    // ----------------------
    // no change to others state
    // no change to supply
    //


    
	// ----------- TEST 1: no treasures in deck - gain nothing --------------
	printf("TEST 1: no treasures in deck - gain nothing\n");




	// ----------- TEST 2: only 1 treasure in deck - +1 in hand  --------------
	printf("TEST 2: 1 treasure in deck - +1 in hand\n");




	// ----------- TEST 3: 2 treasures in deck - +2 in hand  --------------
	printf("TEST 3: 2 treasures in deck - +2 in hand\n");
    




*/
	return 0;
}


