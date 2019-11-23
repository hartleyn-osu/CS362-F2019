#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkHandleMinionCardEffect(int choice1, int handPos, int currentPlayer, struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r;

    r = handleMinionCardEffect();

    assert (r == 0);

    return 0;
    //assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {
    srand(time(NULL));

    int i, n, r, p, deckCount, discardCount, handCount, playerCount, handPos, choice1, estateCount, expected, card;

    int k[10] = {
        adventurer, 
        council_room, 
        feast, 
        gardens, 
        mine,
        remodel, 
        smithy, 
        village, 
        baron, 
        great_hall     
    };

    struct gameState G;

    printf ("Testing handleMinionCardEffect.\n");

    printf ("RANDOM TESTS.\n");

    memset(&G, 23, sizeof(struct gameState));

    int randSeed = rand() % 30;


    for (n = 0; n < 2000; n++) {
        playerCount = rand() % (MAX_PLAYERS - 1) + 2;
        G.whoseTurn = rand() % playerCount;
        choice1 = rand() % 2;

        initializeGame(playerCount, k, randSeed, &G);

        G.handCount[G.whoseTurn] = rand() % (MAX_HAND + 1);

        // randomize hand
        for (int i = 0; i < G.handCount[G.whoseTurn]; i++) {
            if (i == 0 || i == 1)
            {
                G.hand[G.whoseTurn][i] = estate;   
            }
            else
            {
                card = rand() % (treasure_map + 1);
                if (card != estate)
                {
                    G.hand[G.whoseTurn][i];
                }
            }
        }

        handPos = rand() % 2;

        checkHandleMinionCardEffect();

        /*printf("Ran test number %d\n", n + 1);
        printf("Player count: %d\n", playerCount);
        printf("Whose turn: %d\n", G.whoseTurn);
        printf("Hand Count: %d\n", G.handCount[G.whoseTurn]);
        printf("Hand Pos: %d\n", G.hand[G.whoseTurn][0]);
        printf("Hand: %d\n", handPos);
        printf("choice1: %d\n", choice1);*/


        if (choice1 == 1)
        {
            estateCount = 0;
            for (int i = 0; i < G.handCount[G.whoseTurn]; i++) {
                if (G.hand[G.whoseTurn][i] == estate)
                {
                    estateCount++;
                }
            }
            //printf("Estate Count: %d\n\n", estateCount);
            if (estateCount == 1)
            {
                printf("PASS\n");
            }
            else
            {
                printf("Fail\n");
            }
        }  
    }

    //printf ("ALL TESTS OK\n");

    exit(0);

}
