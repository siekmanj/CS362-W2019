/****************************************************************************
* Unit test for isGameOver()
****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include <stdio.h>
#include <string.h>
#include "rngs.h"

#define TESTNAME "isGameOver()"
#define TEST_ID_START 1 

int main() {    
    printf ("*** UNIT TEST BEGIN %s ***\n\n", TESTNAME);
    int test_num = TEST_ID_START; 
    
    int seed = 1000;
    int numPlayers = 2;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    struct gameState initialState; // a blank slate to check against and to reset nextState
    struct gameState nextState; // changes are made to nextState to trigger test results 

    initializeGame(numPlayers, k, seed, &initialState); // initialState is a blank slate 
    memcpy(&nextState, &initialState, sizeof(struct gameState)); // changes are made to 

    assert_print(0, isGameOver(&nextState), "Game not over on init.", &test_num);

    nextState.supplyCount[province] = 0;
    assert_print(1, isGameOver(&nextState), "Game over at 0 province.", &test_num);

    // reset province cards so they do not trigger game over 
    // set 3 other piles to 0 which should trigger game over 
    nextState.supplyCount[province] = 8; 

    // bring all the piles down to size 1 
    for(int i = 0; i <= treasure_map; i++){
        nextState.supplyCount[i] = 1; 
    }
    assert_print(0, isGameOver(&nextState), "Game not over at all piles of size 1", &test_num);

    nextState.supplyCount[adventurer] = 0; 
    assert_print(0, isGameOver(&nextState), "Game not over at 1 empty pile", &test_num);
    nextState.supplyCount[council_room] = 0; 
    assert_print(0, isGameOver(&nextState), "Game not over at 2 empty piles", &test_num);
    nextState.supplyCount[feast] = 0; 

    assert_print(1, isGameOver(&nextState), "Game over at 3 empty piles", &test_num);

    // empty all piles  
    for(int i = 0; i <= treasure_map; i++){
        nextState.supplyCount[i] = 0; 
    }

    assert_print(1, isGameOver(&nextState), "Game over at all empty piles", &test_num);

    memcpy(&nextState, &initialState, sizeof(struct gameState));

    // memcmp returns 0 if the two structs are equal 
    isGameOver(&nextState); 
    assert_print(memcmp(&nextState, &initialState, sizeof(struct gameState)), 0, "Checking game over does not alter state", &test_num);

    printf ("\n*** UNIT TEST END %s   ***\n", TESTNAME);
    return 0;
}
