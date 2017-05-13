// Aimee Sullivan
// CS 362-400 Assignment 4
// 14 May 2017
// randomtestadventurer.c
// Random tests for adventurer card
// Structure of code is based on testDrawCard.c from dominion project code 


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



int checkPlayAdventurer(struct gameState *post, int p){
    char msg[1024];
    int i;
    int preTreasureCount = 0; 
    int preTreasureHand = 0;
    int postTreasureCount = 0; 
    int postTreasureHand = 0;
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));


    for (i = 0; i < pre.handCount[p]; i++){
        if (pre.hand[p][i] == copper || pre.hand[p][i] == silver || pre.hand[p][i] == gold){
            preTreasureHand++;
        }
    }
    for (i = 0; i < pre.deckCount[p]; i++){
        if (pre.deck[p][i] == copper || pre.deck[p][i] == silver || pre.deck[p][i] == gold){
            preTreasureCount++;
        }
    }
    for (i = 0; i < pre.discardCount[p]; i++){
        if (pre.discard[p][i] == copper || pre.discard[p][i] == silver || pre.discard[p][i] == gold){
            preTreasureCount++;
        }
    }
    


//    printf("PRE: treasures in discard & deck: %d in hand: %d\n",preTreasureCount, preTreasureHand);

    //printf("PRE: p %d HC %d DeC %d DiC %d\n",p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);

    
    play_Adventurer(post, p);
    
    for (i = 0; i < post->handCount[p]; i++){
        if (post->hand[p][i] == copper || post->hand[p][i] == silver || post->hand[p][i] == gold){
            postTreasureHand++;
        }
    }
    for (i = 0; i < post->deckCount[p]; i++){
        if (post->deck[p][i] == copper || post->deck[p][i] == silver || post->deck[p][i] == gold){
            postTreasureCount++;
        }
    }
    for (i = 0; i < post->discardCount[p]; i++){
        if (post->discard[p][i] == copper || post->discard[p][i] == silver || post->discard[p][i] == gold){
            postTreasureCount++;
        }
    }
  


//    printf("POST: treasures in discard & deck: %d in hand: %d\n",postTreasureCount, postTreasureHand);

//    printf("POST: p %d HC %d DeC %d DiC %d\n",p, post->handCount[p], post->deckCount[p], post->discardCount[p]);


    if (preTreasureCount >= 2){
        sprintf(msg,"hand = %d, expected = %d", postTreasureHand, preTreasureHand + 2);
        ASSERT2(postTreasureHand == preTreasureHand + 2, msg);
        sprintf(msg,"deck = %d, expected = %d", postTreasureCount, preTreasureCount - 2);
        ASSERT2(postTreasureCount == preTreasureCount - 2, msg);
    } else if (preTreasureCount == 1){
        sprintf(msg,"hand = %d, expected = %d", postTreasureHand, preTreasureHand + 1);
        ASSERT2(postTreasureHand == preTreasureHand + 1, msg);
        sprintf(msg,"deck = %d, expected = %d", postTreasureCount, preTreasureCount - 1);
        ASSERT2(postTreasureCount == preTreasureCount - 1, msg);
    } else {
        sprintf(msg,"hand = %d, expected = %d", postTreasureHand, preTreasureHand);
        ASSERT2(postTreasureHand == preTreasureHand, msg);
        sprintf(msg,"deck = %d, expected = %d", postTreasureCount, preTreasureCount);
        ASSERT2(postTreasureCount == preTreasureCount, msg);
    } 


//    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0;

    return 0;
}




int main(){
    int i, n, p, deckCount, discardCount, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;
    printf("Testing play_Adventurer.\n");
    printf("RANDOM TESTS.\n");
    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++){
        for (i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * MAX_PLAYERS);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        // Random cards in hand
        for (i = 0; i < MAX_HAND; i++){
            G.hand[p][i] = floor(Random() * treasure_map);
        }
        // Random cards in deck and discard
        for (i = 0; i < MAX_DECK; i++){
            G.deck[p][i] = floor(Random() * treasure_map);
            G.discard[p][i] = floor(Random() * treasure_map);
        }
        checkPlayAdventurer(&G, p);
    }





    return 0;
}






/*
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

*/
