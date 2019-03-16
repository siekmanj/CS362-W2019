#ifndef TEST_HELPERS
#define TEST_HELPERS 
#include <stdio.h>
#include <stdlib.h> 
#include "dominion.h" 

void assert_print(int expected, int actual, char* message, int* num);
void assert_print_err(int expected, int actual, char* message);

int countDeckTreasure(int player, struct gameState *game); 
int countHandTreasure(int player, struct gameState *game);
void rand_kc(int k[]);
void rand_hand(int player, struct gameState* G); 
void rand_deck(int player, struct gameState* G); 
void rand_discard(int player, struct gameState* G); 
#endif   
