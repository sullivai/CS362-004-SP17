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
#include <math.h>
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

    // count number of treasures player has (hand, deck, discard)
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
    

    printf("PRE: treasures in discard & deck: %d in hand: %d\n",preTreasureCount, preTreasureHand);
    printf("PRE: p %d HC %d DeC %d DiC %d\n",p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);

    // PLAY THE CARD    
    play_Adventurer(post, p);
    
    // count number of treasures after playing card
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
  
    printf("POST: treasures in discard & deck: %d in hand: %d\n",postTreasureCount, postTreasureHand);
    printf("POST: p %d HC %d DeC %d DiC %d\n",p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

    // ASSERT +2 treasures in hand if 2+ were in deck and/or discard 
    if (preTreasureCount >= 2){
        sprintf(msg,"treasures = %d hand = %d, expected = %d", preTreasureCount, postTreasureHand, preTreasureHand + 2);
        ASSERT2(postTreasureHand == preTreasureHand + 2, msg);
        sprintf(msg,"treasures = %d deck+disc = %d, expected = %d", preTreasureCount, postTreasureCount, preTreasureCount - 2);
        ASSERT2(postTreasureCount == preTreasureCount - 2, msg);

    // ASSERT +1 treasure in hand if 1 was in deck or discard
    } else if (preTreasureCount == 1){
        sprintf(msg,"treasures = %d hand = %d, expected = %d", preTreasureCount, postTreasureHand, preTreasureHand + 1);
        ASSERT2(postTreasureHand == preTreasureHand + 1, msg);
        sprintf(msg,"treasures = %d deck+disc = %d, expected = %d", preTreasureCount, postTreasureCount, preTreasureCount - 1);
        ASSERT2(postTreasureCount == preTreasureCount - 1, msg);

    // ASSERT same number of treasures if there weren't any 
    } else {
        sprintf(msg,"treasures = %d hand = %d, expected = %d", preTreasureCount, postTreasureHand, preTreasureHand);
        ASSERT2(postTreasureHand == preTreasureHand, msg);
        sprintf(msg,"treasures = %d deck+disc = %d, expected = %d", preTreasureCount, postTreasureCount, preTreasureCount);
        ASSERT2(postTreasureCount == preTreasureCount, msg);
    } 

    return 0;
}




int main(){
    int i, n, p;
    struct gameState G;
    printf("Testing play_Adventurer.\n");
    printf("RANDOM TESTS.\n");
    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++){
        // set up game state with random info
        for (i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * MAX_PLAYERS);
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

        // every 100 turns no treasures
        if (n % 100 == 0){
            for (i = 0; i < G.handCount[p]; i++){
                if (G.hand[p][i] >= copper && G.hand[p][i] <= gold){
                    G.hand[p][i] = estate;
                } 
            }
            for (i = 0; i < G.deckCount[p]; i++){
                if (G.deck[p][i] >= copper && G.deck[p][i] <= gold){
                    G.deck[p][i] = estate;
                } 
            }
            for (i = 0; i < G.discardCount[p]; i++){
                if (G.discard[p][i] >= copper && G.discard[p][i] <= gold){
                    G.discard[p][i] = estate;
                } 
            }
        }

        // every 101 turns one treasure
        if (n % 101 == 0){
            for (i = 0; i < G.handCount[p]; i++){
                if (G.hand[p][i] >= copper && G.hand[p][i] <= gold){
                    G.hand[p][i] = estate;
                } 
            }
            for (i = 0; i < G.deckCount[p]; i++){
                if (G.deck[p][i] >= copper && G.deck[p][i] <= gold){
                    G.deck[p][i] = estate;
                } 
            }
            for (i = 0; i < G.discardCount[p]; i++){
                if (G.discard[p][i] >= copper && G.discard[p][i] <= gold){
                    G.discard[p][i] = estate;
                } 
            }
            // select a random treasure (Cu, Ag, or Au)
            int whichtreasure;
            whichtreasure = floor(Random() * 2);
            // select a random place to put it (hand, deck, discard)
            int whichpile;
            whichpile = floor(Random() * 2);
            switch(whichpile){
                case 0: // hand
                        i = floor(Random() * G.handCount[p]);
                        G.hand[p][i] = whichtreasure + copper; 
                        break;
                case 1: // deck
                        i = floor(Random() * G.deckCount[p]);
                        G.deck[p][i] = whichtreasure + copper;
                        break;
                default: // discard
                        i = floor(Random() * G.discardCount[p]);
                        G.discard[p][i] = whichtreasure + copper;
                        break;
            }
        }

        // test card play
        checkPlayAdventurer(&G, p);
    }

    return 0;
}
