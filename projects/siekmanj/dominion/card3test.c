/*
 * card3test.c
 * Testing the mine card.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "mine"

#define NUMPLAYERS 2
#define SEED 1234



int main(){
	struct gameState game, test_game;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(NUMPLAYERS, cards, SEED, &game);

	int choice1 = 0; //The card we are trashing
	int choice2 = 0; //The card we will acquire
	int choice3 = 0;

	int handpos = 0;
	int bonus = 0;

	int current_player = 0;

	int cards_drawn = 1;
	int cards_discarded = 1;

	memcpy(&test_game, &game, sizeof(struct gameState));
	//test with 
	printf("--------TESTING CARD: '%s'--------\n", TESTCARD);

	int test = 1;
	for(int i = copper; i <= gold; i++){
		{
			memcpy(&game, &test_game, sizeof(struct gameState));
			game.hand[current_player][0] = i;
			choice1 = 0;
			choice2 = silver;
			int val1 = getCost(i);
			int val2 = getCost(silver);
			printf("TEST %d: turning treasure of val %d into treasure of val %d.\n", test++, val1, val2);
			int ret = cardEffect(mine, choice1, choice2, choice3, &game, handpos, &bonus);
			printf("	got ret %d\n", ret);
			if(!ret){
				asserttrue(game.hand[current_player][game.handCount[current_player]-1] == silver);
			}else{
				asserttrue(val1 >= val2)
			}
		}
		
		{
			memcpy(&game, &test_game, sizeof(struct gameState));
			game.hand[current_player][0] = i;
			choice1 = 0;
			choice2 = gold;
			int val1 = getCost(i);
			int val2 = getCost(gold);
			printf("TEST %d: turning treasure of val %d into treasure of val %d.\n", test++, val1, val2);
			int ret = cardEffect(mine, choice1, choice2, choice3, &game, handpos, &bonus);
			printf("	got ret %d\n", ret);
			if(!ret){
				int appended_card = game.hand[current_player][game.handCount[current_player]-1];
				printf("returned 0, so %d should be %d\n", appended_card, gold);
				asserttrue(appended_card == gold);
			}else{
				asserttrue(val1 >= val2);
			}
		}
	}

	printf("TEST %d: +1 card to player hand\n", test++);
	printf("	hand count = %d, expected = %d\n", game.handCount[current_player], test_game.handCount[current_player] + cards_drawn - cards_discarded);
	asserttrue(game.handCount[current_player] == test_game.handCount[current_player] + cards_drawn - cards_discarded);


}

