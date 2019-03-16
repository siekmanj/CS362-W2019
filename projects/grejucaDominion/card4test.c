/*
 * card4test.c
 * Testing the council room card.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "council room"
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

	int cards_drawn = 4;
	int cards_discarded = 1;

	//first test to see if there are two more cards in hand
	//test to see if there are two less cards in deck
	//test to see if the cards drawn are a treasure

	printf("--------TESTING CARD: '%s'--------\n", TESTCARD);
	int success = cardEffect(council_room, choice1, choice2, choice3, &game, handpos, &bonus);
	printf("TEST 1: card effect returns 0.\n");
	asserttrue(success == 0);
	

	printf("TEST 2: +4 cards to player hand\n");
	printf("	hand count = %d, expected = %d\n", game.handCount[current_player], test_game.handCount[current_player] + cards_drawn - cards_discarded);
	asserttrue(game.handCount[current_player] == test_game.handCount[current_player] + cards_drawn - cards_discarded);

	printf("TEST 3: -4 cards to player deck\n");
	printf("	deck count = %d, expected = %d\n", game.deckCount[current_player], test_game.deckCount[current_player] - cards_drawn);
	asserttrue(game.deckCount[current_player] == test_game.deckCount[current_player] - cards_drawn);

	printf("TEST 4: +1 buy\n");
	asserttrue(game.numBuys == test_game.numBuys+1);

	int test = 5;
	for(int i = 0; i < NUMPLAYERS; i++){
		if(i!=current_player){
			printf("TEST %d: +1 card to player %d hand:\n", test++, i);
			int player_handcount = game.handCount[i];
			int expected_handcount = test_game.handCount[i]+1;
			asserttrue(player_handcount == expected_handcount);
			printf("TEST %d: -1 card to player %d deck:\n", test++, i);
			int player_deckcount = game.deckCount[i];
			int expected_deckcount = test_game.deckCount[i]-1;
			asserttrue(player_deckcount == expected_deckcount);
		}
	}
}
