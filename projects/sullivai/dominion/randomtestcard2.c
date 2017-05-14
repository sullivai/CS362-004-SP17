// Aimee Sullivan
// CS 362-400 Assignment 4
// 14 May 2017
// randomtestcard2.c
// Random tests for council room card
// Structure of code is based on testDrawCard.c from dominion project code 


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
// http://stackoverflow.com/a/12989329
#define ASSERT2(xy,MSG) do {\
!(xy) ? printf("     TEST FAILED: %s\n",MSG) : printf("TEST PASSED: %s\n",MSG);\
} while(0)

/*
- Draw 4 cards: handCount += 3, deck+discard -= 3
- Get one buy
- All other players draw 1: handCount for them +1, deck+discard -1
- supply piles unaffected
*/

int checkPlayCouncilRoom(struct gameState *post, int p, int handPos){
    char msg[1024];
    int i, n;

    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    
    // sanity check on player hand/deck states
    //for (i = 0; i < MAX_PLAYERS; i++){
    for (i = 0; i < pre.numPlayers; i++){
        printf("...p %d HC %d DeC %d DiC %d\n", \
        i,pre.handCount[i],pre.deckCount[i],pre.discardCount[i]);
    }

    // PLAY THE CARD    
    play_Council_room(post, p, handPos);

    // number of cards gained/lost depends on who is the current player
    //for (i = 0; i < MAX_PLAYERS; i++){
    for (i = 0; i < pre.numPlayers; i++){
        if (i == p){
            n = 3; // gain 4 cards, discard one played
            // Check buys for current player only
            sprintf(msg,"Num buys %d expected %d.",post->numBuys,pre.numBuys+1);
            ASSERT2(post->numBuys == pre.numBuys+1,msg);
        } else {
            n = 1;
        }

        // Check each player's hand count
        sprintf(msg,"Player %d hand %d expected %d", i, post->handCount[i],pre.handCount[i]+n);
        ASSERT2(post->handCount[i] == pre.handCount[i] + n, msg);
        // Check each player's deck/discarded/played count (played only relevant for current player)
        sprintf(msg,"Player %d discard+deck+played %d expected %d", i, \
            post->discardCount[i] + post->deckCount[i] + (i == p ? post->playedCardCount : 0), \
            pre.discardCount[i] + pre.deckCount[i] + (i == p ? pre.playedCardCount : 0 ) - n);        
        ASSERT2(post->discardCount[i] + post->deckCount[i] + (i == p ? post->playedCardCount : 0) \
            == pre.discardCount[i] + pre.deckCount[i] + (i == p ? pre.playedCardCount : 0 ) - n, msg);       
    }

    // check supply piles are the same
    sprintf(msg, "Supply piles unchanged.");
    ASSERT2(memcmp(&pre.supplyCount, post->supplyCount,sizeof(int)*treasure_map) == 0,msg);

    return 0;
}




int main(){
    int i, n, p, handPos;
    struct gameState G;
    printf("Testing play_Council_room.\n");
    printf("RANDOM TESTS.\n");
    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++){
        // set up game state with random info
        for (i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256);
        }

        // make sure there's a nonzero number of players to avoid segfault (thanks gdb)
        G.numPlayers = floor(Random() * (MAX_PLAYERS-1));
        G.numPlayers++;
        //G.numPlayers = MAX_PLAYERS;

        // loop through each player and set up their decks
        //for (p = 0; p < MAX_PLAYERS; p++){
        for (p = 0; p < G.numPlayers; p++){
            G.deckCount[p] = floor(Random() * MAX_DECK);
            G.discardCount[p] = floor(Random() * MAX_DECK);
            G.handCount[p] = floor(Random() * MAX_HAND);
        }

        // set up supply piles with random values
        for (i = 0; i < treasure_map; i++){
            G.supplyCount[i] = floor(Random() * MAX_DECK);
        } 
       
        // choose a player and set turn
        //p = floor(Random() * MAX_PLAYERS);
        p = floor(Random() * G.numPlayers);
        G.whoseTurn = p;
        G.numBuys = 1;

        // Random cards in played 
        G.playedCardCount = floor(Random() * MAX_DECK);

        // pick a random handPos for card to be played
        handPos = floor(Random() * (G.handCount[p] - 1));
        
        printf("player %d, handcount %d, handpos %d, notHandcount %d\n",p, G.handCount[p], handPos, G.discardCount[p]+G.deckCount[p]+G.playedCardCount);

        // test card play
        checkPlayCouncilRoom(&G, p, handPos);
    }

    return 0;
}
