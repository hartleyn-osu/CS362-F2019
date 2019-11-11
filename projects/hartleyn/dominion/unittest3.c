//#include "card_effect_handlers.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int main () {
    printf ("Starting\n");
    int i, n, r, p, deckCount, discardCount, handCount, estateCount;

    int k[10] = { ambassador, estate, estate, gardens, mine, remodel, smithy, village, adventurer, great_hall };

    struct gameState G;
    
    for (i = 0; i < 10; i++)
    {   
        G.hand[0][i] = k[i];
    }
    
    r = handleAmbassadorCardEffect(1, 10, 0, 0, &G);
    
    assert(r == -1);

    printf ("ALL TESTS OK\n");

    exit(0);
}
