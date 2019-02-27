#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "adventurer"

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
		if(!is_card_in_cards(adventurer, cards, card_count)){
			cards[rand()%card_count] = adventurer;
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
		printf("cards: %d\nplayers %d\ncurrent player: %d\nchoice1: %d\nchoice2: %d\nchoice3: %d\nhandpos: %d\nbonus: %d\n", card_count, player_count, current_player, choice1, choice2, choice3, handpos, bonus);

		cardEffect(adventurer, choice1, choice2, choice3, &game, handpos, &bonus);
		printf("TEST %d: +2 cards to player hand\n", tests++);
		printf("	hand count = %d, expected = %d\n", game.handCount[current_player], test_game.handCount[current_player] + cards_drawn - cards_discarded);
		asserttrue(game.handCount[current_player] == test_game.handCount[current_player] + cards_drawn - cards_discarded);

		printf("TEST %d: -2 cards to player deck\n", tests++);
		printf("	deck count = %d, expected = %d\n", game.deckCount[current_player], test_game.deckCount[current_player] - cards_drawn);
		asserttrue(game.deckCount[current_player] == test_game.deckCount[current_player] - cards_drawn);

		printf("TEST %d: +2 treasure cards to player hand:\n", tests++);
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

		printf("TEST %d: -2 treasure cards from player deck:\n", tests++);
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
}

