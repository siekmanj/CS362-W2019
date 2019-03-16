/****************************************************************************
* Unit test for council room
****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include <stdio.h>
#include <string.h>
#include "rngs.h"

#define TESTNAME "council room"
#define TEST_ID_START 1


int main() {    
    printf ("*** UNIT TEST BEGIN %s ***\n\n", TESTNAME);

    int c1 = 0, c2 = 0, c3 = 0, handpos = 0, bonus = 0; 
    int player = 0, newcards = 4, discards = 1; 
    int test_num = TEST_ID_START; 
    
    int seed = 1000;
    int numPlayers = 2;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    struct gameState initialState; // a blank slate to check against and to reset nextState
    struct gameState nextState; // changes are made to nextState to trigger test results 

    initializeGame(numPlayers, k, seed, &initialState); // initialState is a blank slate 
    memcpy(&nextState, &initialState, sizeof(struct gameState)); // changes are made to nextState

    cardEffect(council_room, c1, c2, c3, &nextState, handpos, &bonus);

    assert_print(initialState.handCount[player] + newcards - discards, nextState.handCount[player], "Net 3 cards added to hand", &test_num);
    assert_print(initialState.deckCount[player] - newcards, nextState.deckCount[player], "Net 4 cards removed from deck", &test_num);
    assert_print(initialState.discardCount[player] + discards, nextState.discardCount[player], "Discard increased by 1", &test_num);
    assert_print(initialState.numBuys + 1, nextState.numBuys, "Add 1 buy to the player", &test_num);

    // check that the common piles of cards were not altered 
    int altered = 0; 
    for(int i = 0; i <= treasure_map; i++){
        if(initialState.supplyCount[i] != nextState.supplyCount[i]) {
            altered++;
            break;
        }  
    }
 
    assert_print(altered, 0, "Victory, kingdom, and coin piles unaltered", &test_num);

    assert_print(initialState.handCount[player + 1] + 1, nextState.handCount[player + 1], "one card added to player 2 hand", &test_num); 
    assert_print(initialState.deckCount[player + 1] - 1, nextState.deckCount[player + 1], "one card removed from player 2 deck", &test_num);
    assert_print(initialState.discardCount[player + 1], nextState.discardCount[player + 1], "player 2 discard unchanged", &test_num);
    
    printf ("\n*** UNIT TEST END %s   ***\n", TESTNAME);
    return 0;
}
