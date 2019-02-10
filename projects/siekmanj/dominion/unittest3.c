/*
 * unittest3.c
 * Testing the updateCoins function.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTFUNC "updateCoins"
#define NUMPLAYERS 2
#define SEED 1234

int main(){
	struct gameState game, test_game;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(NUMPLAYERS, cards, SEED, &game);
	memcpy(&test_game, &game, sizeof(struct gameState));

	int player = 0;
	int coin_types[] = {copper, silver, gold};
	printf("--------TESTING FUNCTION: '%s'--------\n", TESTFUNC);

	//This runs 10 tests, with a pseudorandom combination of coppper, silver, and gold.
	//Because the seed is the same every time, it is deterministic and will always have
	//the same result.
	for(int i = 1; i < 10;){
		int expected_value = 0;
		memcpy(&game, &test_game, sizeof(struct gameState));
		for(int i = 0; i < game.handCount[player]; i++){
			int coin = coin_types[rand() % 3]; 
			game.hand[player][i] = coin; 
			if(coin == copper) expected_value += 1;
			if(coin == silver) expected_value += 2;
			if(coin == gold  ) expected_value += 3;
		}
		int bonus = rand() % 5;
		int ret = updateCoins(player, &game, bonus);
		printf("TEST %d: returned 0:\n", i++);
		asserttrue(ret == 0);
		printf("TEST %d: expected hand value: %d coins.\n", i++, expected_value + bonus);
		int actual_value = game.coins;
		asserttrue(actual_value == expected_value + bonus);
	}
	
	//This tests to make sure that when the player's hand has no coins, 
	//updateCoins sets game.coins to zero.
	printf("Test 11: Testing with no coins in hand.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	for(int i = 0; i < game.handCount[player]; i++){
		game.hand[player][i] = village;
	}
	updateCoins(player, &game, 0);
	asserttrue(game.coins == 0);

	//This tests to make sure that when the player's hand is empty, 
	//updateCoins sets game.coins to zero.
	printf("Test 12: Testing with hand of size zero.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	game.handCount[player] = 0;
	updateCoins(player, &game, 0);
	asserttrue(game.coins == 0);
}


