// Aimee Sullivan
// CS 362-400 Assignment 4
// 14 May 2017
// randomtestcard1.c
// Random tests for mine card
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

int checkPlayMine(struct gameState *post, int p, int handPos, int ch1, int ch2){
    char msg[1024];
    int r; //, i;

    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    // PLAY THE CARD    
    //r = play_Mine(post, p, handPos, ch1, ch2);
    r = cardEffect(mine,ch1,ch2,0,post,handPos,0);

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

    return 0;
}




int main(){
    int i, n, p, handPos, ch1, ch2;
    struct gameState G;
    printf("Testing play_Mine.\n");
    printf("RANDOM TESTS.\n");
    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++){
        // set up game state with random info
        for (i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * MAX_PLAYERS);
        G.whoseTurn = p;
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_DECK);
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
        // Random cards in played 
        for (i = 0; i < G.playedCardCount; i++){
            G.playedCards[i] = floor(Random() * treasure_map);
        }

        // pick a random handPos for card to be played
        handPos = floor(Random() * (G.handCount[p] - 1));
        
        // pick a random card to trash from hand
        ch1 = floor(Random() * (G.handCount[p] - 1));

        // pick a random card to gain from supply
        ch2 = floor(Random() * treasure_map);

        printf("player %d, handcount %d, handpos %d, ch1 %d, cost %d, ch2 %d, cost %d\n",p, G.handCount[p], handPos, G.hand[p][ch1], getCost(G.hand[p][ch1]), ch2, getCost(ch2));

        // test card play
        checkPlayMine(&G, p, handPos, ch1, ch2);
    }

    return 0;
}
