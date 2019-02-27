#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "smithy"

#define NUMPLAYERS 2
#define SEED 1234

int get_random_card(){
	int low = adventurer;
	int high = treasure_map;
	int range = high-low;
	return (rand() % range) + low;
}

int is_card_in_cards(int c, int *cards, size_t len){
	for(int i = 0; i < len; i++){
		if(c == cards[i]){
			printf("%d is in cards.\n", c);
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
			printf("got card: %d\n", c);
		}
		while(is_card_in_cards(c, cards, len));
		cards[i] = c;
	}
}
int main(){
	int trials = 2000;
	while(trials --> 0){ //trials goes to 0

		int card_count = (rand() % 19) + 1; // there are only 19 possible action cards
		int player_count = (rand() % 4) + 1; // dominion.h limits max players to 4
		printf("testing card count of %d, player count %d \n", card_count, player_count);

		struct gameState game, test_game;
		int cards[card_count];	
		make_random_deck(cards, card_count);
		if(!is_card_in_cards(smithy, cards, card_count)){
			cards[rand()%card_count] = smithy;
			printf("had to add smithy.\n");
		}
		//exit(1);

		initializeGame(player_count, cards, SEED, &game);
		memcpy(&test_game, &game, sizeof(struct gameState));

		int choice1 = 0;
		int choice2 = 0;
		int choice3 = 0;

		int handpos = 0;
		int bonus = 0;

		//int current_player = 0;

		//int cards_drawn = 3;
		//int cards_discarded = 1;

		printf("--------TESTING CARD: '%s'--------\n", TESTCARD);
		cardEffect(smithy, choice1, choice2, choice3, &game, handpos, &bonus);
	}
}
