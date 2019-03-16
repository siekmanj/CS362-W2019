#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "village"

int get_random_card(){
	int low = copper;
	int high = treasure_map;
	int range = high-low;
	return (rand() % range) + low;
}

int get_random_action(){
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

void make_random_actions(int *cards, size_t len){
	for(int i = 0; i < len; i++){
		int c;
		do{
			c = get_random_action();
		}
		while(is_card_in_cards(c, cards, len));
		cards[i] = c;
	}
}

void make_random_deck(int *cards, size_t len){
	for(int i = 0; i < len; i++)
		cards[i] = get_random_card();
}

#define TRIALS 250
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
		make_random_actions(cards, card_count);
		if(!is_card_in_cards(village, cards, card_count)){
			cards[rand()%card_count] = village;
		}

		initializeGame(player_count, cards, SEED, &game);
		for(int i = 0; i < player_count; i++){
			int decksize = rand() % MAX_DECK;
			int handsize = rand() % MAX_HAND;
			make_random_deck(game.hand[i], handsize);
			make_random_deck(game.deck[i], decksize);
		}
		game.whoseTurn = current_player;
		memcpy(&test_game, &game, sizeof(struct gameState));

		cardEffect(village, choice1, choice2, choice3, &game, handpos, &bonus);

		//check to see that one card was gained from deck
		printf("Test %d: hand count +1 -1.\n", tests++);
		asserttrue(game.handCount[current_player] == test_game.handCount[current_player]);
		printf("Test %d: deck count -1\n", tests++);
		asserttrue(game.deckCount[current_player] == test_game.deckCount[current_player] - 1);
		printf("Test %d: action count +2\n", tests++);
		asserttrue(game.numActions == test_game.numActions + 2);
		printf("Test %d: discard +1\n", tests++);
		asserttrue(game.discardCount[current_player] == test_game.discardCount[current_player]+1);
	}
}
