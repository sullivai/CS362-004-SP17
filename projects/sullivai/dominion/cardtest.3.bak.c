// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// cardtest3.c
// Unit tests for smithy card
// Structure of code is based on cardtest4.c provided in Assignment 3 Assistance 
// in course materials.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"
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
    int extraBuys = 1;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);
    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = council_room;    
	memcpy(&testG, &G, sizeof(struct gameState));

    for (thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++){
        printf("player:%d hand:%d, deck:%d, discard:%d,  played:%d\n",thisPlayer,G.handCount[thisPlayer],G.deckCount[thisPlayer],G.discardCount[thisPlayer],G.playedCardCount);
        for (j = 0; j<G.handCount[thisPlayer]; j++){
            printf("  %d  ",G.hand[thisPlayer][j]);
        }
        printf("\n");
        for (j = 0; j<G.playedCardCount; j++){
            printf("  %d  ",G.playedCards[j]);
        }
        printf("\n");
    }
thisPlayer=0;
handpos=0;
printf("handpos:%d card playing: %d\n",handpos, G.hand[thisPlayer][handpos]);    
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);


    for (thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++){
        printf("player:%d hand:%d, deck:%d, discard:%d, played:%d\n",thisPlayer,testG.handCount[thisPlayer],testG.deckCount[thisPlayer],testG.discardCount[thisPlayer],testG.playedCardCount);
        for (j = 0; j<testG.handCount[thisPlayer]; j++){
            printf("  %d  ",testG.hand[thisPlayer][j]);
        }
        printf("\n");
        for (j = 0; j<G.playedCardCount; j++){
            printf("  %d  ",G.playedCards[j]);
        }
        printf("\n");
    }

    thisPlayer = 0;
	newCards = 4;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	printf("played count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + discarded);
    printf("played card = %d, expected = %d\n", testG.playedCards[testG.playedCardCount-1], council_room);
    printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + extraBuys);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);


/*
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);
*/


//unfix dom.c
// hand +4./
// deck -4./
// buys+1./
// hand-1./
// discard+1../
// card in played./
// others+1hand
// others-1deck
//
//
//test 1 - check shit above


//test 2 - loop num players
//check num cards in hand
//check num cards in deck
//



	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: play TESTCARD and check all values are updated correctly for player --------------
	printf("\nTEST 1: play %s - draw 4/discard 1 = +3 in hand, -4 in deck, +1 buy, +0 coins\n",TESTCARD);
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);

    thisPlayer = 0;
    handpos = 0;

    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = council_room;    
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
    printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    printf("played count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + discarded);
    printf("played card = %d, expected = %d\n", testG.playedCards[testG.playedCardCount-1], council_room);
    printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + extraBuys);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
    // check kingdom and victory supply piles
    for (j = 0; j <= treasure_map; j++){
        printf("supply[%d] = %d, expected %d\n",j,testG.supplyCount[j],G.supplyCount[j]);
        assert(testG.supplyCount[j] == G.supplyCount[j]);
    }
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
    assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
    assert(testG.playedCardCount == G.playedCardCount + discarded);
    assert(testG.playedCards[testG.playedCardCount-1] == council_room);
    assert(testG.numBuys == G.numBuys + extraBuys);
    assert(testG.coins == G.coins + xtraCoins);
    
	// ----------- TEST 2: loop position of TESTCARD in player's hand --------------
	printf("\nTEST 2: loop position of %s in player's hand - correct card gets played\n",TESTCARD);
	// initialize a game state and player cards
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);

    for (handpos = 0; handpos < G.handCount[thisPlayer]; handpos++){
        // put TESTCARD in player's hand
        G.hand[thisPlayer][handpos] = council_room;    
        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
        printf("handpos = %d, played card = %d, expected = %d\n", handpos, testG.playedCards[testG.playedCardCount-1], council_room);
        assert(testG.playedCards[testG.playedCardCount-1] == council_room);
        
        memset(&G,'\0',sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &G);
    }


	// ----------- TEST 3: check other players hands --------------
	printf("\nTEST 3: check other players +1 in hand, -1 in deck\n",TESTCARD);
	// initialize a game state and player cards
    numPlayers = MAX_PLAYERS;
    memset(&G,'\0',sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &G);

    thisPlayer = 0;
    handpos = 0;
    newCards = 1;

    // put TESTCARD in player's hand
    G.hand[thisPlayer][handpos] = council_room;    
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

    // check other players' hand/deck/discard 
    for (j = 1; j < numPlayers; j++){
        printf("\nPlayer %d:\n",j);
        printf("hand count = %d, expected = %d\n", testG.handCount[j], G.handCount[j] + newCards);
        printf("deck count = %d, expected = %d\n", testG.deckCount[j], G.deckCount[j] - newCards);
        printf("discard count = %d, expected = %d\n", testG.discardCount[j], G.discardCount[j]);
        assert(testG.handCount[j] == G.handCount[j] + newCards);
        assert(testG.deckCount[j] == G.deckCount[j] - newCards);
        assert(testG.discardCount[j] == G.discardCount[j]);
    }




/*
	// ----------- TEST 4: loop player playing TESTCARD --------------
	printf("\nTEST 4: loop player number playing %s\n",TESTCARD);
    numPlayers = MAX_PLAYERS;

    for (thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++){
        handpos = 0;
        // initialize a game state and player cards
        memset(&G,'\0',sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &G);
        // put TESTCARD in player's hand
        G.whoseTurn = thisPlayer;
        G.hand[thisPlayer][handpos] = council_room;    
        memcpy(&testG, &G, sizeof(struct gameState));

        for (j = 0; j<testG.handCount[thisPlayer]; j++){
            printf("  %d  ",testG.hand[thisPlayer][j]);
        }
        printf("\n");
        for (j = 0; j<G.playedCardCount; j++){
            printf("  %d  ",G.playedCards[j]);
        }
        printf("\n");
        cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
        for (j = 0; j<testG.handCount[thisPlayer]; j++){
            printf("  %d  ",testG.hand[thisPlayer][j]);
        }
        printf("\n");
        for (j = 0; j<G.playedCardCount; j++){
            printf("  %d  ",G.playedCards[j]);
        }
        printf("\n");
        printf("thisPlayer = %d\n",thisPlayer);
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
        printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
        printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
        printf("played count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + discarded);
        printf("played card = %d, expected = %d\n", testG.playedCards[testG.playedCardCount-1], council_room);
        printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys + extraBuys);
        printf("coins = %d, expected = %d\n\n", testG.coins, G.coins + xtraCoins);
        //assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
        //assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
        //assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);
        //assert(testG.playedCardCount == G.playedCardCount + discarded);
        //assert(testG.playedCards[testG.playedCardCount-1] == council_room);
        //assert(testG.numBuys == G.numBuys + extraBuys);
        //assert(testG.coins == G.coins + xtraCoins);
    }
*/

	return 0;
}


