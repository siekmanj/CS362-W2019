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

int is_card_in_cards(int c, int cards, size_t len){
	for(int i = 0; i < len; i++){
		if(c = cards[i])
			return 1;
	}
	return 0;
}

int main(){
	int trials = 2000;
	while(trials --> 0){ //trials goes to 0

		struct gameState game, test_game;
		int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
		
		int num_cards = 0;
		for(int i = 0; i < 10; i++){
			card c;
			do{

			}
			while(is_card_in_cards(c, cards, num_cards));

		}

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
	}
}
