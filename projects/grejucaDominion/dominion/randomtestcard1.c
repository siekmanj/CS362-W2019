/****************************************************************************
* Random tests for adventurerEffect
****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h> 
#include "rngs.h"
#include <time.h> 

#define TESTNAME "council room"
#define TEST_ID_START 1 

int testCouncil(int player, struct gameState* G){
    struct gameState preG;
    memcpy(&preG, G, sizeof(struct gameState)); 

    // these should not affect council room play via discardCard() function 
    int c1 = rand() % MAX_HAND; 
    int c2 = rand() % MAX_HAND; 
    int c3 = rand() % MAX_HAND; 
    int hp = rand() % MAX_DECK; 
    int bonus = rand() % 1000; // a generous upper limit for bonus to test boundary  


    cardEffect(council_room, c1, c2, c3, G, hp, &bonus);

    // check expected effect on current player 
    assert_print_err(preG.handCount[player] + 3, G->handCount[player], "Net 3 cards added to hand");
    assert_print_err(preG.deckCount[player] - 4, G->deckCount[player], "Net 4 cards removed from deck");
    assert_print_err(preG.discardCount[player] + 1, G->discardCount[player], "Discard increased by 1");
    assert_print_err(preG.numBuys + 1, G->numBuys, "Add 1 buy to the player");

    // check expected effects on other players 
    // update expected changes to avoid false side effect error
    for(int i = 0; i < G->numPlayers; i++){
        if(i != player){
            assert_print_err(preG.handCount[i] + 1, G->handCount[i], "one card added to player 2 hand"); 
            assert_print_err(preG.deckCount[i] - 1, G->deckCount[i], "one card removed from player 2 deck");
            assert_print_err(preG.discardCount[i], G->discardCount[i], "player 2 discard unchanged");
        }

        // deck, hand, discard, and playedCards (and counts) can all be expected to change 
        // set them to be equal to avoid false trigger of side effect error 
        // copy preG into G because G may have some out of bounds counts due to buggy code 
        memcpy(G->deck[i], preG.deck[i], sizeof(int) * MAX_DECK);
        G->deckCount[i] = preG.deckCount[i]; 

        memcpy(G->hand[i], preG.hand[i], sizeof(int) * MAX_HAND);
        G->handCount[i] = preG.handCount[i];

        memcpy(G->playedCards, preG.playedCards, sizeof(int) * MAX_DECK);
        G->playedCardCount = preG.playedCardCount;
    }

    // only the current player should have an altered discard
    memcpy(G->discard[player], preG.discard[player], sizeof(int) * MAX_DECK);
    G->discardCount[player] = preG.discardCount[player];
    preG.numBuys++; 

    if(memcmp(&preG, G, sizeof(struct gameState)) != 0) {
      printf("\tFAIL side effect found\n"); 
    }
    return 0; 
}

int main() {
  printf ("*** RANDOM TEST BEGIN %s ***\n\n", TESTNAME);
  srand(time(NULL));    
  struct gameState G; 

  for(int i = 0; i < 2000; i++){
    int k[10]; 
    rand_kc(k); // randomize kingom card set 
    
    // randomize players 
    int numPlayers = (rand() % MAX_PLAYERS) + 1; // add 1 to avoid 0 players 
    int player = rand() % numPlayers;

    int seed = rand(); 

    initializeGame(numPlayers, k, seed, &G);  // init game to properly set everything

    // further randomize the game
    // do this for all players since council room interacts with other player piles 
    for(int j = 0; j < numPlayers; j++){  
        rand_hand(player, &G);
        rand_deck(player, &G);
        rand_discard(player, &G);
    }  

    G.whoseTurn = player; 
    testCouncil(player, &G);
  }
    printf ("\n*** UNIT TEST END %s   ***\n", TESTNAME);
    return 0;
}
