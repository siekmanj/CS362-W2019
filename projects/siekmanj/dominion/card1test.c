/*
 * card1test.c
 * Testing the smithy card.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "smithy"
#define SHOULD_PRINT 1

#define NUMPLAYERS 2
#define SEED 1234

int main(){
	struct gameState game, test_game;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(NUMPLAYERS, cards, SEED, &game);
	memcpy(&test_game, &game, sizeof(struct gameState));

	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

	int handpos = 0;
	int bonus = 0;

	int current_player = 0;

	int cards_drawn = 3;
	int cards_discarded = 1;

	printf("--------TESTING CARD: '%s'--------\n", TESTCARD);
	cardEffect(smithy, choice1, choice2, choice3, &game, handpos, &bonus);

	printf("TEST 1: using smithy (+3 cards to player hand)\n");
	printf("	hand count = %d, expected = %d\n", game.handCount[current_player], test_game.handCount[current_player] + cards_drawn - cards_discarded);
	asserttrue(game.handCount[current_player] == test_game.handCount[current_player] + cards_drawn - cards_discarded);

	printf("TEST 2: using smithy (-3 cards to player deck)\n");
	printf("	deck count = %d, expected = %d\n", game.deckCount[current_player], test_game.deckCount[current_player] - cards_drawn);
	asserttrue(game.deckCount[current_player] == test_game.deckCount[current_player] - cards_drawn);
	
	int test = 3;
	for(int i = 0; i < NUMPLAYERS; i++){
		if(i != current_player){
			printf("TEST %d: Checking to make sure player %d hand is not changed.\n", test++, i);
			asserttrue(game.handCount[i] == test_game.handCount[i]);
			printf("TEST %d: Checking to make sure player %d deck is not changed.\n", test++, i);
			asserttrue(game.deckCount[i] == test_game.deckCount[i]);
		}
	}
}
