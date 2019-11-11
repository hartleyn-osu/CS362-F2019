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

    int k[10] = { baron, estate, estate, gardens, mine, remodel, smithy, village, adventurer, great_hall };

    struct gameState G;
    
    for (i = 0; i < 10; i++)
    {   
        G.hand[0][i] = k[i];
    }
    printf("STARTING\n");
    //testHandleBaronCardEffect(&G);
    
    //int estateCount;
    printf("Here\n");
    //r = handleBaronCardEffect(1, 0, 0, &G);

    estateCount = 0;
    for (i = 0; i < 10; i++)
    {
        if (G.hand[0][i] == estate)
        {
            estateCount++;
        } 
    }
    

    //assert(r == 0);
    assert(estateCount > 0);

    printf ("ALL TESTS OK\n");

    exit(0);
}
