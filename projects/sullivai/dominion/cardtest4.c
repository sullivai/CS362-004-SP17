// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// cardtest4.c
// Unit tests for mine card
// Structure of code is based on cardtest4.c provided in Assignment 3 Assistance 
// in course materials.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"
// http://stackoverflow.com/a/12989329
#define ASSERT2(xy,MSG) do {\
!(xy) ? printf("     TEST FAILED: %s\n",MSG) : printf("TEST PASSED: %s\n",MSG);\
} while(0)

/*
- hand contains 0, 1, 2 treasure cards
- hand contains coppers - get silver
- hand contains silvers - get gold
- num cards in hand is same (-1 to discard?)
- no other state changes except treasure supply maybe
- coins increase
- buys stay same
- correct card (gold or silver) is in trash
- gaincard(s) --> goes into hand
- mine is discarded into trash

choice1 is card to trash
-- test choice1 is treasure card

choice2 is card to gain
-- test choice2 is treasure and valid supply pile
*/


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
/*
test 1: choice1 = copper, choice2 = copper  OK
gaincard --> goes into hand
mine is discarded into trash
cost of c2 > cost of c1 + 3
- num cards in hand is same (-1 to discard?)
- no other state changes except treasure supply maybe
- coins increase
- buys stay same
- correct card (gold or silver) is in trash
choice1 = copper, choice2 = silver OK
choice1 = copepr, choice2 = gold FAIL
choice1 = copper, choice2 = nontreasure worth 3 FAIL (village)
choice1 = silver, choice2 = nontreasure worth more FAIL (adventurer)
*/

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = copper, choice2 = copper --------------
	printf("\nTEST 1a: play %s - choice1 = Cu, choice2 = Cu\n",TESTCARD);
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    thisPlayer = 0;
    newCards = 1;   
    handpos = 0;
    extraBuys = 0;
    choice1 = 1;        // handpos of card to trash
    choice2 = copper;
    xtraCoins = 0;

    // put TESTCARD and choice card in player's hand
    G.hand[thisPlayer][handpos] = mine;
    G.hand[thisPlayer][choice1] = copper;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // supply piles
    for (j = 0; j <= treasure_map; j++){
        if (j == choice2){
            sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]); ///////
            ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
        } else {
            sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]);
            ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
        }
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
    // buys
    sprintf(msg,"buys = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    ASSERT2(testG.numBuys == G.numBuys + extraBuys, msg);
    // coins
    sprintf(msg,"coins = %d, expected = %d", testG.coins, G.coins + xtraCoins);
    ASSERT2(testG.coins == G.coins + xtraCoins, msg);
    
	printf("\nTEST 1b: play %s - choice1 = Cu, choice2 = Ag\n",TESTCARD);
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    thisPlayer = 0;
    newCards = 1;   
    handpos = 0;
    extraBuys = 0;
    choice1 = 1;        // handpos of card to trash
    choice2 = silver;
    xtraCoins = 3;

    // put TESTCARD and choice card in player's hand
    G.hand[thisPlayer][handpos] = mine;
    G.hand[thisPlayer][choice1] = copper;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // supply piles
    for (j = 0; j <= treasure_map; j++){
        if (j == choice2){
            sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j-1]);
            ASSERT2(testG.supplyCount[j] == G.supplyCount[j-1], msg);
        } else {
            sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]);
            ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
        }
    }
    // hand count should be same
    sprintf(msg,"hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer]-discarded);
    ASSERT2(testG.handCount[thisPlayer] == G.handCount[thisPlayer]-discarded, msg);
    // deck count should be same
    sprintf(msg,"deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    ASSERT2(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], msg);
    // discard count
    sprintf(msg,"discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+discarded);
    ASSERT2(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]+discarded, msg);
    // played count
    sprintf(msg,"played count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + discarded);
    // buys
    sprintf(msg,"buys = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    ASSERT2(testG.numBuys == G.numBuys + extraBuys, msg);
    // coins
    sprintf(msg,"coins = %d, expected = %d", testG.coins, G.coins + xtraCoins);
    ASSERT2(testG.coins == G.coins + xtraCoins, msg);
 
	printf("\nTEST 1c: play %s - choice1 = Cu, choice2 = Au\n",TESTCARD);
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    thisPlayer = 0;
    newCards = 1;   
    handpos = 0;
    extraBuys = 0;
    choice1 = 1;        // handpos of card to trash
    choice2 = gold;
    xtraCoins = 0;

    // put TESTCARD and choice card in player's hand
    G.hand[thisPlayer][handpos] = mine;
    G.hand[thisPlayer][choice1] = copper;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // supply piles
    for (j = 0; j <= treasure_map; j++){
        if (j == choice2){
            sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]);
            ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
        } else {
            sprintf(msg,"supply[%d] = %d, expected %d",j,testG.supplyCount[j],G.supplyCount[j]);
            ASSERT2(testG.supplyCount[j] == G.supplyCount[j], msg);
        }
    }
    // hand count
    sprintf(msg,"hand count = %d, expected = %d", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    ASSERT2(testG.handCount[thisPlayer] == G.handCount[thisPlayer],msg);
    // deck count
    sprintf(msg,"deck count = %d, expected = %d", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    ASSERT2(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], msg);
    // discard count
    sprintf(msg,"discard count = %d, expected = %d", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    ASSERT2(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer], msg);
    // played count
    sprintf(msg,"played count = %d, expected = %d", testG.playedCardCount, G.playedCardCount);
    ASSERT2(testG.playedCardCount == G.playedCardCount, msg);
    // buys
    sprintf(msg,"buys = %d, expected = %d", testG.numBuys, G.numBuys + extraBuys);
    ASSERT2(testG.numBuys == G.numBuys + extraBuys, msg);
    // coins
    sprintf(msg,"coins = %d, expected = %d", testG.coins, G.coins);
    ASSERT2(testG.coins == G.coins, msg);

/*
test2: choice1 = silver, choice2 = copper OK
choice1 = silver, choice2 = silver OK
choice1 = silver choice2 = gold OK
choice1 = silver choice2 = nontreas worth 6 (adventurer) FAIL
*/


/*
test3: hand contains 0 treasure cards
- deck was shuffled?
- mine discarded
- nothing else changes
- coin supplies same
- coins of player stay same

hand contains 1 treasure
- deck shuffled
- mine discarded
- coins increase
- change in coin supply dep on what choice1 was and choice 2

hand contains 2 treasures
- mine discarded 
- coin supplies change
- player coins change dep on choice 1/2
*/

/*
test4 c1 is not a treasure card - FAIL
- no change to states
*/

/*
test5 c2 is not a treasure cards - FAIL
- no change to states
*/

/*
test 6 cost of ch2 > cost of ch1 + 3 -- FAIL
*/




	return 0;
}


