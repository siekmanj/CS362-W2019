/*
 * unittest1.c
 * Testing the fullDeckCount function.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTFUNC "fullDeckCount"
#define NUMPLAYERS 2
#define SEED 1234

int main(){
	struct gameState game, test_game;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(NUMPLAYERS, cards, SEED, &game);
	memcpy(&test_game, &game, sizeof(struct gameState));

	int player = 0;
	printf("--------TESTING FUNCTION: '%s'--------\n", TESTFUNC);

	int count = 0;
	for(int i = curse; i < treasure_map; i++){
		memcpy(&game, &test_game, sizeof(struct gameState)); //reset game
		int count = 0;
		for(int j = 0; j < game.deckCount[player]; j++){
			if(!(rand()%3)){ //1/3 chance of inserting card (seed is always the same, so not random)
				count++;
				game.deck[player][j] = i;
			}
		}
		for(int j = 0; j < game.handCount[player]; j++){
			if(!(rand()%3)){ //1/3 chance of inserting card
				count++;
				game.hand[player][j] = i;
			}

		}
		for(int j = 0; j < game.discardCount[player]; j++){
			if(!(rand()%3)){ //1/3 chance of inserting card
				count++;
				game.discard[player][j] = i;
			}
		}
		printf("TEST %d: inserting %d of card value of %d into deck.\n", i, count, i);
		asserttrue(fullDeckCount(player, i, &game) == count);
	}

	printf("TEST %d: passing invalid card value to function.\n", treasure_map);
	int card = -1;
	memcpy(&game, &test_game, sizeof(struct gameState)); //reset game
	count = fullDeckCount(player, card, &game);
	asserttrue(count == 0);



}
