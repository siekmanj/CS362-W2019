/*
 * card2test.c
 * Testing the adventurer card.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "adventurer"
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

	int cards_drawn = 2;
	int cards_discarded = 1;

	//first test to see if there are two more cards in hand
	//test to see if there are two less cards in deck
	//test to see if the cards drawn are a treasure

	printf("--------TESTING CARD: '%s'--------\n", TESTCARD);
	cardEffect(adventurer, choice1, choice2, choice3, &game, handpos, &bonus);

	printf("TEST 1: +2 cards to player hand\n");
	printf("	hand count = %d, expected = %d\n", game.handCount[current_player], test_game.handCount[current_player] + cards_drawn - cards_discarded);
	asserttrue(game.handCount[current_player] == test_game.handCount[current_player] + cards_drawn - cards_discarded);

	printf("TEST 2: -2 cards to player deck\n");
	printf("	deck count = %d, expected = %d\n", game.deckCount[current_player], test_game.deckCount[current_player] - cards_drawn);
	asserttrue(game.deckCount[current_player] == test_game.deckCount[current_player] - cards_drawn);

	printf("TEST 3: +2 treasure cards to player hand:\n");
	int new_treasure_count = 0;
	for(int i = 0; i < game.handCount[current_player]; i++){
		int current_card = game.hand[current_player][i];
		if(current_card == copper || current_card == silver || current_card == gold)
			new_treasure_count++;
	}
	int old_treasure_count = 0;
	for(int i = 0; i < test_game.handCount[current_player]; i++){
		int current_card = test_game.hand[current_player][i];
		if(current_card == copper || current_card == silver || current_card == gold)
			old_treasure_count++;
		
	}
	printf("	treasures in new hand = %d, treasures in old hand = %d\n", new_treasure_count, old_treasure_count);
	asserttrue(new_treasure_count == old_treasure_count+2);

	printf("TEST 4: -2 treasure cards from player deck:\n");
	new_treasure_count = 0;
	for(int i = 0; i < game.deckCount[current_player]; i++){
		int current_card = game.deck[current_player][i];
		if(current_card == copper || current_card == silver || current_card == gold)
			new_treasure_count++;
	}
	old_treasure_count = 0;
	for(int i = 0; i < test_game.deckCount[current_player]; i++){
		int current_card = test_game.deck[current_player][i];
		if(current_card == copper || current_card == silver || current_card == gold)
			old_treasure_count++;
	}
	printf("	treasures in new deck = %d, treasures in old deck = %d\n", new_treasure_count, old_treasure_count);
	asserttrue(new_treasure_count == old_treasure_count-2);

}

