#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "smithy"

int get_random_card(){
	int low = adventurer;
	int high = treasure_map;
	int range = high-low;
	return (rand() % range) + low;
}

int is_card_in_cards(int c, int *cards, size_t len){
	for(int i = 0; i < len; i++){
		if(c == cards[i]){
			return 1;
		}
	}
	return 0;
}

void make_random_deck(int *cards, size_t len){
	for(int i = 0; i < len; i++){
		int c;
		do{
			c = get_random_card();
		}
		while(is_card_in_cards(c, cards, len));
		cards[i] = c;
	}
}
#define TRIALS 2000
int main(){
	int trials = TRIALS;
	int SEED = time(NULL);
	int tests = 1;
	printf("--------TESTING CARD: '%s'--------\n", TESTCARD);
	while(trials --> 0){ //trials goes to 0

		int card_count = (rand() % 19) + 1; // there are only 19 possible action cards, can't have 0
		int player_count = (rand() % 4) + 1; // dominion.h limits max players to 4, can't have 0
		int current_player = (rand() % player_count);

		int choice1 = rand();
		int choice2 = rand();
		int choice3 = rand(); //should have no effect

		int cards_drawn = 3;
		int cards_discarded = 1;

		int handpos = rand()%MAX_HAND;
		int bonus = rand();

		struct gameState game, test_game;
		int cards[card_count];	
		make_random_deck(cards, card_count);
		if(!is_card_in_cards(smithy, cards, card_count)){
			cards[rand()%card_count] = smithy;
		}

		initializeGame(player_count, cards, SEED, &game);
		game.whoseTurn = current_player;
		memcpy(&test_game, &game, sizeof(struct gameState));
		printf("cards: %d\nplayers %d\ncurrent player: %d\nchoice1: %d\nchoice2: %d\nchoice3: %d\nhandpos: %d\nbonus: %d\n", card_count, player_count, current_player, choice1, choice2, choice3, handpos, bonus);

		cardEffect(smithy, choice1, choice2, choice3, &game, handpos, &bonus);
		//test to make sure three carsds added
		printf("Test %d: using smithy (+3 cards to player hand)\n", tests++);
		asserttrue(game.handCount[current_player] == test_game.handCount[current_player] + cards_drawn - cards_discarded);

		//test to make sure one card discarded
		printf("Test %d: using smithy (+1 cards to player discard pile)\n", tests++);
		asserttrue(game.discardCount[current_player] + cards_discarded == test_game.discardCount[current_player]);
		//test to make sure all other players cards are the same

		for(int i = 0; i < player_count; i++){
			if(i != current_player){
				printf("Test %d: Checking to see that player %d's hand has not changed.\n", tests++, i);
				asserttrue(game.handCount[i] == test_game.handCount[i]);
				printf("Test %d: Checking to see that player %d's deck has not changed.\n", tests++, i);
				asserttrue(game.deckCount[i] == test_game.deckCount[i]);
			}
		}
	}
}
