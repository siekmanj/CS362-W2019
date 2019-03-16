/*
 * unittest1.c
 * Testing the isGameOver function.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTFUNC "isGameOver"
#define NUMPLAYERS 2
#define SEED 1234

int main(){
	struct gameState game, test_game;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("--------TESTING FUNCTION: '%s'--------\n", TESTFUNC);
	initializeGame(NUMPLAYERS, cards, SEED, &game);
	memcpy(&test_game, &game, sizeof(struct gameState));
	game.supplyCount[province] = 0;
	printf("TEST 1: Game should end when provinces are 0.\n");
	asserttrue(isGameOver(&game) == 1);

	printf("TEST 2: Game should end when any three supply piles are empty.\n");
	int fail = 0;
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){
			if(i != j){
				for(int k = 0; k < 25; k++){
					if(j != k && i != k){
						memcpy(&game, &test_game, sizeof(struct gameState));
						game.supplyCount[i] = 0;
						game.supplyCount[j] = 0;
						game.supplyCount[k] = 0;
						if(!isGameOver(&game)){
							fail = 1;
							i = 25;
							j = 25;
							k = 25;
						}
					}
				}
			}
		}
	}
	asserttrue(fail == 0);

	printf("TEST 3: Game should not end when there is at least one province left.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	game.supplyCount[province] = 1;
	asserttrue(isGameOver(&game) == 0);

	printf("TEST 4: Game should not end when at least three supply piles are not empty.\n");
	memcpy(&game, &test_game, sizeof(struct gameState));
	fail = 0;
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){
			if(i != j){
				for(int k = 0; k < 25; k++){
					if(j != k && i != k){
						memcpy(&game, &test_game, sizeof(struct gameState));
						game.supplyCount[i] = 1;
						game.supplyCount[j] = 1;
						game.supplyCount[k] = 1;
						if(isGameOver(&game)){
							fail = 1;
							i = 25;
							j = 25;
							k = 25;
						}
					}
				}
			}
		}
	}
	asserttrue(fail == 0);
}
