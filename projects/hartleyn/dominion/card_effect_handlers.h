#ifndef _CARD_EFFECT_HANDLERS_H
#define _CARD_EFFECT_HANDLERS_H

#include "dominion.h"

int handleBaronCardEffect(int choice1, int handPos, int currentPlayer, 
                          struct gameState *state);
int handleMinionCardEffect(int choice1, int choice2, int handPos, 
                           int currentPlayer, struct gameState *state);
int handleAmbassadorCardEffect(int choice1, int choice2, int handPos, 
                               int currentPlayer, struct gameState *state);
int handleTributeCardEffect(int currentPlayer, int nextPlayer, struct gameState *state);
int handleMineCardEffect(int choice1, int choice2, int handPos, 
                         int currentPlayer, struct gameState *state);

#endif
