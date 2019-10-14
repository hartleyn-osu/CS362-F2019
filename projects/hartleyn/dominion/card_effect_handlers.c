#include "dominion.h"
#include "dominion_helpers.h"
#include "card_effect_handlers.h"

int handleBaronCardEffect(int choice1, int handPos, int currentPlayer, struct gameState *state)
{
    //Increase buys by 1!
    state->numBuys++;

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    if (choice1 > 0) { //Boolean true or going to discard an estate
        int p = 0;//Iterator for hand!
        int card_not_discarded = 1;//Flag for discard set!

        while(card_not_discarded) {
            if (state->hand[currentPlayer][p] == estate) { //Found an estate card!
                state->coins += 4;//Add 4 coins to the amount of coins

                //discard estate card
                discardCard(p, currentPlayer, state, 0);

                //BUG 1
                //card_not_discarded = 0;//Exit the loop
            }
            else if (p > state->handCount[currentPlayer]) {
                if(DEBUG) {
                    printf("No estate cards in your hand, invalid choice\n");
                    printf("Must gain an estate if there are any\n");
                }
                if (supplyCount(estate, state) > 0) {
                    gainCard(estate, state, 0, currentPlayer);

                    state->supplyCount[estate]--;//Decrement estates

                    if (supplyCount(estate, state) == 0) {
                        isGameOver(state);
                    }
                }

                card_not_discarded = 0;//Exit the loop
            }
            else {
                p++;//Next card
            }
        }
    }
    else {
        // BUG 2
        //if (supplyCount(estate, state) > 0) {
        if (supplyCount(estate, state) > 1) {
            gainCard(estate, state, 0, currentPlayer);//Gain an estate

            state->supplyCount[estate]--;//Decrement Estates
            if (supplyCount(estate, state) == 0) {
                isGameOver(state);
            }
        }
    }

    return 0;
}

int handleMinionCardEffect(int choice1, int choice2, int handPos, int currentPlayer, struct gameState *state)
{
    int i;
    int j;

    //+1 action
    state->numActions++;

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    if (choice1)
    {
        //BUG 2
        //state->coins = state->coins + 2;
        state->coins =  2;
    }
    else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    {
        //discard hand
        while(numHandCards(state) > 0)
        {
            discardCard(handPos, currentPlayer, state, 0);
        }

        //draw 4
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, state);
        }

        //BUG 1
        //other players discard hand and redraw if hand size > 4
        //for (i = 0; i < state->numPlayers; i++)
        for (i = 0; i < state->numPlayers-1; i++)
        {
            if (i != currentPlayer)
            {
                if ( state->handCount[i] > 4 )
                {
                    //discard hand
                    while( state->handCount[i] > 0 )
                    {
                        discardCard(handPos, i, state, 0);
                    }

                    //draw 4
                    for (j = 0; j < 4; j++)
                    {
                        drawCard(i, state);
                    }
                }
            }
        }
    }

    return 0;
}

int handleAmbassadorCardEffect(int choice1, int choice2, int handPos, int currentPlayer, struct gameState *state)
/*
    Handle amabassador effects
*/
{
    int i;
    int j = 0;      //used to check if player has enough cards to discard
    int trash_card_index;

    // BUG 1
    //if (choice2 > 2 || choice2 < 0)
    if (choice2 < 0)
    {
        return -1;
    }

    if (choice1 == handPos)
    {
        return -1;
    }

    for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
        if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
        {
            j++;
        }
    }
    if (j < choice2)
    {
        return -1;
    }

    if (DEBUG)
        printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

    // BUG 2
    //increase supply count for choosen card by amount being discarded
    //state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

    //each other player gains a copy of revealed card
    for (i = 0; i < state->numPlayers; i++)
    {
        if (i != currentPlayer)
        {
            gainCard(state->hand[currentPlayer][choice1], state, 0, i);
        }
    }

    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //trash copies of cards returned to supply
    for (j = 0; j < choice2; j++)
    {
        trash_card_index = findCardHandIndex(state->hand[currentPlayer][choice1], currentPlayer, state);
        
        //discard trashed card
        discardCard(trash_card_index, currentPlayer, state, 1);
    }

    return 0;
}

int handleTributeCardEffect(int currentPlayer, int nextPlayer, struct gameState *state)
{
    int i;
    int tributeRevealedCards[2] = {-1, -1};

    if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
        if (state->deckCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = setTributeCard(nextPlayer, state->deck, state->deckCount);
        }
        else if (state->discardCount[nextPlayer] > 0) {
            //BUG 1
            //tributeRevealedCards[0] = setTributeCard(nextPlayer, state->discard, state->discardCount);
            tributeRevealedCards[0] = setTributeCard(currentPlayer, state->discard, state->discardCount);
        }
        else {
            //No Card to Reveal
            if (DEBUG) {
                printf("No cards to reveal\n");
            }
        }
    }

    else {
        if (state->deckCount[nextPlayer] == 0) {
            for (i = 0; i < state->discardCount[nextPlayer]; i++) {
                state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                state->deckCount[nextPlayer]++;
                state->discard[nextPlayer][i] = -1;
                state->discardCount[nextPlayer]--;
            }

            shuffle(nextPlayer,state);//Shuffle the deck
        }
        tributeRevealedCards[0] = setTributeCard(nextPlayer, state->deck, state->deckCount);
        //BUG 2
        //tributeRevealedCards[1] = setTributeCard(nextPlayer, state->deck, state->deckCount);
        tributeRevealedCards[0] = setTributeCard(nextPlayer, state->deck, state->deckCount);
    }

    if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
        state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
        state->playedCardCount++;
        tributeRevealedCards[1] = -1;
    }

    for (i = 0; i <= 2; i ++) {
        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
            state->coins += 2;
        }

        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
            drawCard(currentPlayer, state);
            drawCard(currentPlayer, state);
        }
        else { //Action Card
            state->numActions = state->numActions + 2;
        }
    }

    return 0;
}

int handleMineCardEffect(int choice1, int choice2, int handPos, int currentPlayer, struct gameState *state)
{
    int i;
    int trash_card_index;

    if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
    {
        return -1;
    }

    //BUG 1
    //if (choice2 > treasure_map || choice2 < curse)
    if (choice2 > treasure_map && choice2 < curse)
    {
        return -1;
    }

    //BUG 2
    //if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
    if (getCost(state->hand[currentPlayer][choice1]) > getCost(choice2) )
    {
        return -1;
    }

    gainCard(choice2, state, 2, currentPlayer);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    trash_card_index = findCardHandIndex(state->hand[currentPlayer][choice1], currentPlayer, state);

    if (trash_card_index < 0)
    {
        return -1;
    }

    //discard trashed card
    discardCard(trash_card_index, currentPlayer, state, 1);

    return 0;
}
