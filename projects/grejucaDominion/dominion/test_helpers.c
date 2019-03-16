#include "test_helpers.h"
 

void assert_print(int expected, int actual, char* message, int* num){
    printf("\tTest %i ", *num);
    (*num)++; 
	if(expected == actual) printf("PASS %s\n", message); 
	else printf("FAIL %s | EXPECTED: %i | ACTUAL: %i\n", message, expected, actual); 
}

void assert_print_err(int expected, int actual, char* message){
	if(expected != actual)
	    printf("\tFAIL %s | EXPECTED: %i | ACTUAL: %i\n", message, expected, actual);
}

// counts the number of treasure cards in a deck 
int countDeckTreasure(int player, struct gameState *game) {
  int card, index, count = 0;
  for(index = 0; index < game->deckCount[player]; index++) {
    card = game->deck[player][index];
    switch(card) {
    case copper: count++;
      break;
    case silver: count++;
      break;
    case gold: count++;
      break;
    }
  }
  return count;
}

// counts the numbeer of treasure cards in a hand 
int countHandTreasure(int player, struct gameState *game) {
  int card, index, count = 0;
  for(index = 0; index < game->handCount[player]; index++) {
    card = game->hand[player][index];
    switch(card) {
    case copper: count++;
      break;
    case silver: count++;
      break;
    case gold: count++;
      break;
    }
  }
  return count;
}

// generate a random set of kc (all cards in set are unique)
void rand_kc(int k[]){
    // create a random set of kingdom cards  
    for(int i = 0; i < 10; i++){
      int same = 1; 
      int card; 
      while(same){
        card = rand() % (treasure_map + 1);
        same = 0; 
        for(int j = 0; j < i; j++){
          if(card == k[j]) same = 1;
        }
      }

      k[i] = card;
    }
}

// generate a random hand 
void rand_hand(int player, struct gameState* G){
    G->handCount[player] = rand() % (MAX_HAND + 1); 

    // create a random hand 
    for(int i = 0; i < G->handCount[player]; i++){
      G->hand[player][i] = rand() % (treasure_map + 1);
    }
}

// generate a random deck 
void rand_deck(int player, struct gameState* G){
    G->deckCount[player] = rand() % (MAX_HAND + 1);

    for(int i = 0; i < G->deckCount[player]; i++){
      G->deck[player][i] = rand() % (treasure_map + 1);
    }
}

// generate a random discard pile 
void rand_discard(int player, struct gameState* G){
    // discardCount is incremented in dominion in a way that can cause seg faults
    // setting the count to MAX / 2 reduces the liklihood of an array out of bounds 
    G->discardCount[player] = rand() % (MAX_HAND / 2);

    for(int i = 0; i < G->deckCount[player]; i++){
      G->discard[player][i] = rand() % (treasure_map + 1);
    }
}
