#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int adventurerEffect(int currentPlayer, int tempHand[], int cardDrawn, 
		struct gameState *state);
int councilRoomEffect(int currentPlayer, int handPos, struct gameState *state);
int feastEffect(int choice1, int currentPlayer, int tempHand[], 
		struct gameState *state);
int mineEffect(int choice1, int choice2, int currentPlayer, 
		int handPos, struct gameState *state);
int smithyEffect(int currentPlayer, int handPos, struct gameState *state);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

#endif
