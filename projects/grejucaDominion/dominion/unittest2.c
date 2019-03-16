/****************************************************************************
* Unit test for discardCard()
****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include <stdio.h>
#include <string.h>
#include "rngs.h"

#define TESTNAME "discardCard()"
#define TEST_ID_START 1 

int main() {    
    printf ("*** UNIT TEST BEGIN %s ***\n\n", TESTNAME);
    int test_num = TEST_ID_START; 
    
    int handpos = 0, player = 1; 

    int seed = 100;
    int numPlayers = 2;
    
    int k[10] = {treasure_map, sea_hag, feast, gardens, mine
               , remodel, smithy, village, cutpurse, great_hall};

    struct gameState initialState; // a blank slate to check against and to reset nextState
    struct gameState nextState; // changes are made to nextState to trigger test results 

    initializeGame(numPlayers, k, seed, &initialState); // initialState is a blank slate 
    memcpy(&nextState, &initialState, sizeof(struct gameState)); 

    // test discardCard on player2 
    discardCard(handpos, player, &nextState, 0); 
    assert_print(initialState.discardCount[player], nextState.discardCount[player], "Discard count increases by 1", &test_num);
    assert_print(initialState.handCount[player] - 1, nextState.handCount[player], "Hand count decreases by 1", &test_num);

    memcpy(&nextState, &initialState, sizeof(struct gameState)); 

    handpos = nextState.handCount[player] - 1; 
    discardCard(handpos, player, &nextState, 0); 
    assert_print(initialState.discardCount[player], nextState.discardCount[player], "Discard count unchanged (last card in hand)", &test_num);
    assert_print(initialState.handCount[player] - 1, nextState.handCount[player], "Hand count decreases by 1 (last card in hand)", &test_num);

    memcpy(&nextState, &initialState, sizeof(struct gameState)); 

    handpos = 1;
    nextState.handCount[player] = 1; 
    discardCard(handpos, player, &nextState, 0); 
    assert_print(initialState.discardCount[player], nextState.discardCount[player], "Discard count unchanged (only 1 card in hand)", &test_num);
    assert_print(initialState.handCount[player] - 1, nextState.handCount[player], "Hand count decreases by 1 (only card in hand)", &test_num);

    memcpy(&nextState, &initialState, sizeof(struct gameState)); 

    discardCard(handpos, player, &nextState, 1); 
    assert_print(initialState.discardCount[player] + 1, nextState.discardCount[player], "Discard count increases by 1 (not trashed)", &test_num);
    assert_print(initialState.handCount[player] - 1, nextState.handCount[player], "Hand count decreases by 1 (not trashed)", &test_num);

    // check player 2 is unaltered 
    assert_print(0, memcmp(initialState.hand[player - 1], nextState.hand[player - 1], sizeof(initialState.hand[player + 1])), "other player hand unchanged", &test_num); 
    assert_print(0, memcmp(initialState.deck[player - 1], nextState.deck[player - 1], sizeof(initialState.hand[player + 1])), "other player deck unchanged", &test_num);
    assert_print(0, memcmp(initialState.discard[player - 1], nextState.discard[player - 1], sizeof(initialState.hand[player + 1])), "other player discard unchanged", &test_num);

    // check that the common piles of cards were not altered 
    int altered = 0; 
    for(int i = 0; i <= treasure_map; i++){
        if(initialState.supplyCount[i] != nextState.supplyCount[i]) {
            altered++;
            break;
        }  
    }
 
    assert_print(altered, 0, "Victory, kingdom, and coin piles unaltered", &test_num);
    printf ("\n*** UNIT TEST END %s   ***\n", TESTNAME);
    return 0;
}
