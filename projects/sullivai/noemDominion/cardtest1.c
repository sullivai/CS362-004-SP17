// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// cardtest1.c
// Unit tests for smithy card
// Structure of code is based on cardtest4.c provided in Assignment 3 Assistance 
// in course materials.

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
// http://stackoverflow.com/a/12989329
#define ASSERT2(xy,MSG) do {\
!(xy) ? printf("     TEST FAILED: %s\n",MSG) : printf("TEST PASSED: %s\n",MSG);\
} while(0)



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
    //cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    sSmithy(&testG, thisPlayer, handpos);
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

	// ----------- TEST 2: loop position of TESTCARD in player's hand --------------
	printf("\nTEST 2: loop position of %s in player's hand - correct card gets played\n",TESTCARD);
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);

    for (handpos = 0; handpos < G.handCount[thisPlayer]; handpos++){
        // put TESTCARD in player's hand
        G.hand[thisPlayer][handpos] = smithy;    
        memcpy(&testG, &G, sizeof(struct gameState));
        //cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
        sSmithy(&testG, thisPlayer, handpos);
        // card in played pile
        sprintf(msg,"handpos = %d, played card = %d, expected = %d", handpos, testG.playedCards[testG.playedCardCount-1], smithy);
        ASSERT2(testG.playedCards[testG.playedCardCount-1] == smithy, msg);
        
        memset(&G,'\0',sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &G);
    }


	// ----------- TEST 3: check other players hands --------------
	printf("\nTEST 3: check other players hands and decks unchanged\n");
	// initialize a game state and player cards
    numPlayers = MAX_PLAYERS;
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);

    thisPlayer = 0;
    handpos = 0;
    newCards = 0;

    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = smithy;    
    memcpy(&testG, &G, sizeof(struct gameState));
    //cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    sSmithy(&testG, thisPlayer, handpos);

    // check other players' hand/deck/discard 
    for (j = 1; j < numPlayers; j++){
        printf("\nPlayer %d:\n",j);
        // other players hand count
        sprintf(msg,"hand count = %d, expected = %d", testG.handCount[j], G.handCount[j] + newCards);
        ASSERT2(testG.handCount[j] == G.handCount[j] + newCards,msg);
        // other players deck count
        sprintf(msg,"deck count = %d, expected = %d", testG.deckCount[j], G.deckCount[j] - newCards);
        ASSERT2(testG.deckCount[j] == G.deckCount[j] - newCards,msg);
        // other players discard count
        sprintf(msg,"discard count = %d, expected = %d", testG.discardCount[j], G.discardCount[j]);
        ASSERT2(testG.discardCount[j] == G.discardCount[j],msg);
    }


	return 0;
}


