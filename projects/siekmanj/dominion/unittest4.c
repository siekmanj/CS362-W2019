/*
 * unittest4.c
 * Testing the endTurn function.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTFUNC "endTurn"
#define NUMPLAYERS 2
#define SEED 1234

int main(){
	struct gameState game, test_game;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(NUMPLAYERS, cards, SEED, &game);
	memcpy(&test_game, &game, sizeof(struct gameState));

	int player = 0;
	int next_player = 1;

	printf("--------TESTING FUNCTION: '%s'--------\n", TESTFUNC);
	
	printf("TEST 1: Checking if next player is picked correctly.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	endTurn(&game);
	asserttrue(game.whoseTurn == next_player);

	printf("TEST 2: Checking if next player is picked correctly when current player is the last player.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	endTurn(&game);
	endTurn(&game);
	asserttrue(game.whoseTurn == player);

	printf("TEST 3: Checking if cards were discarded correctly.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	int tmp[game.handCount[player]];
	for(int i = 0; i < game.handCount[player]; i++){
		tmp[i] = game.hand[player][i];
	}	
	endTurn(&game);
	int success = 1;
	for(int i = 0; i < game.discardCount[player]; i++){
		if(tmp[i] != game.discard[player][i]){
			success = 0;
			break;
		}
	}
	asserttrue(success == 1);

	printf("TEST 4: Checking if five cards were drawn.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	endTurn(&game);
	asserttrue(game.handCount[next_player] == 5);

	printf("TEST 5: Checking to make sure all other player's hands are empty.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	endTurn(&game);
	success = 1;
	for(int i = 0; i < NUMPLAYERS; i++){
		if(game.handCount[i] > 0 && i != next_player) success = 0;
	}
	asserttrue(success == 1);
}
