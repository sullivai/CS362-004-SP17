// Aimee Sullivan
// CS 362-400 Assignment 3
// 30 April 2017
// unittest2.c
// Unit tests for isGameOver() function in dominion.c
// Structure of code is based on testUpdateCoins.c provided in Assignment 3 Assistance 2
// in course materials.
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// http://stackoverflow.com/a/12989329
#define ASSERT2(xy,MSG) do {\
!(xy) ? printf("     TEST FAILED: %s\n",MSG) : printf("TEST PASSED: %s\n",MSG);\
} while(0)



int main() {
    char msg[1024] = {'\0'};
    int i, r, gameover;
    // stuff to set up game state
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                smithy, village, baron, great_hall};
    struct gameState G;

    printf("\n\n#####################################################\n");
    printf("##             TESTING isGameOver():               ##\n");
    printf("#####################################################\n");
    
    // TEST 1: No provinces, game is over
    printf("\nTest 1: provinces condition\n");

    // Initialize game
    memset(&G,'\0',sizeof(struct gameState));
    r = initializeGame(numPlayer,k,seed,&G);
    assert(!r);  

    // Test 1, 0, -1 provinces
    for (i = 1; i >= -1; i--){
        G.supplyCount[province] = i;
        gameover = isGameOver(&G);
        sprintf(msg,"Provinces: %d, game is %sover",i,(gameover ? "" : "not "));
        ASSERT2(isGameOver(&G) != i, msg);
    }
    
    // TEST 2: Provinces but 3 or more supply piles are empty, game is over
    printf("\nTest 2: provinces but empty supply piles condition\n");

    // Loop through all supply cards and 0 out three piles at a time, then check status
    for (i = 0; i <= treasure_map-2; i++){
        memset(&G,'\0',sizeof(struct gameState));
        r = initializeGame(numPlayer,k,seed,&G);
        assert(!r); 
        // skip zeroing province pile
        if(i == province-2 || i == province-1 || i == province) continue;
        G.supplyCount[i] = 0;
        G.supplyCount[i+1] = 0;
        G.supplyCount[i+2] = 0;
        gameover = isGameOver(&G);
        sprintf(msg,"pile %d = %d; pile %d = %d; pile %d = %d; game is %sover",i,G.supplyCount[i],i+1,G.supplyCount[i+1],i+2,G.supplyCount[i+2],(gameover ? "" : "not "));
        ASSERT2(isGameOver(&G),msg);
    }
 
    
    // TEST 3: Provinces and 2 or fewer supply piles are empty, games is not over
    printf("\nTest 3: provinces and 2 or fewer empty supply piles condition\n");

    // Loop through all supply cards and 0 out two piles at a time, then check status
    for (i = 0; i <= treasure_map-2; i++){
        memset(&G,'\0',sizeof(struct gameState));
        r = initializeGame(numPlayer,k,seed,&G);
        assert(!r); 
        // skip zeroing province pile
        if(i == province-1 || i == province) continue;
        G.supplyCount[i] = 0;
        G.supplyCount[i+1] = 0;
        gameover = isGameOver(&G);
        sprintf(msg,"pile %d = %d; pile %d = %d; pile %d = %d; game is %sover",i,G.supplyCount[i],i+1,G.supplyCount[i+1],i+2,G.supplyCount[i+2],(gameover ? "" : "not "));
        ASSERT2(!isGameOver(&G),msg);
    }


    return 0;
}
