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
- Draw 4 cards - handCount += 3, deck+discard -= 3
- Get one buy
- All other players draw 1 - handCount for them +1, deck+discard -1
- supply piles unaffected
*/

int checkPlayCouncilRoom(struct gameState *post, int p, int handPos){
    char msg[1024];

    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    // PLAY THE CARD    
    play_Council_room(post, p, handPos);
/*
    // bad choice 1
    if (post->hand[p][ch1] < copper || post->hand[p][ch1] > gold){
        sprintf(msg,"Returned choice 1 incorrect type %d, expect 4, 5, or 6.", post->hand[p][ch1]);
        ASSERT2(r == -1 && (post->hand[p][ch1] < copper || post->hand[p][ch1] > gold) ,msg);
        sprintf(msg, "No state change.");
        ASSERT2(memcmp(&pre, post, sizeof(struct gameState)) == 0,msg);
    }

    // bad choice 2
    if (ch2 < copper || ch2 > gold){
        sprintf(msg,"Returned choice 2 incorrect type %d, expect 4, 5, or 6.", ch2);
        ASSERT2(r == -1 && (ch2 < copper || ch2 > gold),msg);
        sprintf(msg, "No state change.");
        ASSERT2(memcmp(&pre, post, sizeof(struct gameState)) == 0,msg);
    }

    // choice 2 too expensive
    if (getCost(post->hand[p][ch1]) + 3 < getCost(ch2)){
        sprintf(msg,"Returned card too expensive (cost is %d, limit is %d)",getCost(ch2),getCost(post->hand[p][ch1])+3);
        ASSERT2(r == -1 && getCost(post->hand[p][ch1]) + 3 < getCost(ch2),msg);
        sprintf(msg, "No state change.");
        ASSERT2(memcmp(&pre, post, sizeof(struct gameState)) == 0,msg);
    }
    

    if (r == 0){
        // if all OK and card is played, then handcount--, discard++, ch1 supply++, ch2 supply--    
        sprintf(msg, "POST handcount %d, expected %d.", post->handCount[p],pre.handCount[p]-1);
        ASSERT2(post->handCount[p] == pre.handCount[p]-1,msg);
        sprintf(msg, "POST discardcount %d, expected %d.", post->discardCount[p],pre.discardCount[p]+1);
        ASSERT2(post->discardCount[p] == pre.discardCount[p]+1,msg);
        sprintf(msg, "POST ch1 supply count %d, expected %d.", post->supplyCount[pre.hand[p][ch1]],pre.supplyCount[pre.hand[p][ch1]]+1);
        ASSERT2(post->supplyCount[pre.hand[p][ch1]] == pre.supplyCount[pre.hand[p][ch1]]+1,msg);
        sprintf(msg, "POST ch2 supply count %d, expected %d.", post->supplyCount[ch2], pre.supplyCount[ch2]);
        ASSERT2(post->supplyCount[ch2] == pre.supplyCount[ch2]-1,msg);
    }
*/
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

        // loop through each player and set up their decks
        for (p = 0; p < MAX_PLAYERS; p++){
            G.deckCount[p] = floor(Random() * MAX_DECK);
            G.discardCount[p] = floor(Random() * MAX_DECK);
            G.handCount[p] = floor(Random() * MAX_HAND);
            // Random cards in hand
            for (i = 0; i < G.handCount[p]; i++){
                G.hand[p][i] = floor(Random() * treasure_map);
            }
            // Random cards in deck 
            for (i = 0; i < G.deckCount[p]; i++){
                G.deck[p][i] = floor(Random() * treasure_map);
            }
            // Random cards in discard 
            for (i = 0; i < G.discardCount[p]; i++){
                G.discard[p][i] = floor(Random() * treasure_map);
            }
        }
        
        // set this player
        p = floor(Random() * MAX_PLAYERS);
        G.whoseTurn = p;

        // Random cards in played 
        G.playedCardCount = floor(Random() * MAX_DECK);
        for (i = 0; i < G.playedCardCount; i++){
            G.playedCards[i] = floor(Random() * treasure_map);
        }

        // pick a random handPos for card to be played
        handPos = floor(Random() * (G.handCount[p] - 1));
        
//        printf("player %d, handcount %d, handpos %d, ch1 %d, cost %d, ch2 %d, cost %d\n",p, G.handCount[p], handPos, G.hand[p][ch1], getCost(G.hand[p][ch1]), ch2, getCost(ch2));

        // test card play
        checkPlayCouncilRoom(&G, p, handPos);
    }

    return 0;
}
