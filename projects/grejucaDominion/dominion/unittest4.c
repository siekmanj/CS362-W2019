/****************************************************************************
* Unit test for playCard()
****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include <stdio.h>
#include <string.h>
#include "rngs.h"

#define TESTNAME "playCard()"
#define TEST_ID_START 1 

int main() {    
    printf ("*** UNIT TEST BEGIN %s ***\n\n", TESTNAME);
    int test_num = TEST_ID_START; 
    
    int c1 = 0, c2 = 1, c3 = 2, handpos = 0, player = 0; 

    int seed = 100;
    int numPlayers = 2;
    
    int k[10] = {treasure_map, sea_hag, feast, gardens, ambassador
               , remodel, smithy, village, cutpurse, great_hall};

    struct gameState initialState; // a blank slate to check against and to reset nextState
    struct gameState nextState; // changes are made to nextState to trigger test results 

    initializeGame(numPlayers, k, seed, &initialState); // initialState is a blank slate 

    initialState.phase = 0; 
    initialState.numActions = 5; 
    initialState.hand[player][handpos] = smithy;

    memcpy(&nextState, &initialState, sizeof(struct gameState)); 

    int was_successful = 0; 

    // this tests multiple hand positions as well as the correct update to numActions
    for(int i = 0; i < nextState.handCount[player]; i++){
        nextState.hand[player][i] = sea_hag;
        was_successful = playCard(i, c1, c2, c3, &nextState); 
    }

    assert_print(0, was_successful, "test success of a valid play", &test_num); 
    assert_print(0, nextState.numActions, "test use up of five actions on five successfuly plays", &test_num); 

    memcpy(&nextState, &initialState, sizeof(struct gameState)); 
    nextState.hand[player][handpos + 3] = village;
    nextState.numActions = 1; 
    playCard(handpos, c1, c2, c3, &nextState); 
    assert_print(0, nextState.numActions, "test play card on boundary (only one action remaining)", &test_num);   

    nextState.numActions = 0; 
    assert_print(-1, playCard(handpos, c1, c2, c3, &nextState), "No action if numActions < 1", &test_num); 

    memcpy(&nextState, &initialState, sizeof(struct gameState)); 
    nextState.phase = 1; 
    assert_print(-1, playCard(handpos, c1, c2, c3, &nextState), "No action if incorrect phase (!= 0)", &test_num); 
    assert_print(initialState.numActions, nextState.numActions, "numActions unchanged if incorrect phase and play attempt is made", &test_num);  

    memcpy(&nextState, &initialState, sizeof(struct gameState));
    nextState.hand[player][handpos] = copper;   
    assert_print(-1, playCard(handpos, c1, c2, c3, &nextState), "test attempted use of nonaction card (low boundary)", &test_num); 

    nextState.hand[player][handpos + 1] = treasure_map + 1;   
    assert_print(-1, playCard(handpos + 1, c1, c2, c3, &nextState), "test attempted use of nonaction card (high boundary)", &test_num); 

    nextState.hand[player][handpos] = smithy; 
    nextState.handCount[player] = 0; 
    assert_print(-1, playCard(handpos, c1, c2, c3, &nextState), "test attempted play with empty hand", &test_num); 

    memcpy(&nextState, &initialState, sizeof(struct gameState)); 
    nextState.hand[player][handpos] = ambassador;
    assert_print(-1, playCard(handpos, handpos, c2, c3, &nextState), "test bad choice which results in no cardEffect", &test_num);


    printf ("\n*** UNIT TEST END %s   ***\n", TESTNAME);
    return 0;
}
