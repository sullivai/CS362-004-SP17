#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
    int maxBonus = 10;
    int p,r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++){
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++){
        for (handCount = 1; handCount <= maxHandCount; handCount++){
            for(bonus = 0; bonus <= maxBonus; bonus++){
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure cards and %d bonus.\n",p,handCount,bonus);
#endif
                memset(&G,'\0',sizeof(struct gameState));
                r = initializeGame(numPlayer,k,seed,&G);
                G.handCount[p] = handCount;
                memcpy(G.hand[p],coppers,sizeof(int)*handCount);
                updateCoins(p,&G,bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n",G.coins,handCount*1+bonus);
#endif
                assert(G.coins == handCount*1+bonus);
                memcpy(G.hand[p],silvers,sizeof(int)*handCount);
                updateCoins(p,&G,bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n",G.coins,handCount*2+bonus);
#endif
                assert(G.coins == handCount*2+bonus);
                memcpy(G.hand[p],golds,sizeof(int)*handCount);
                updateCoins(p,&G,bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n",G.coins,handCount*3+bonus);
#endif
                assert(G.coins == handCount*3+bonus);
            }
        }
    }
    printf("All tests passed.\n");
    return 0;
}
