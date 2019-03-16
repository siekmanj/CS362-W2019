/****************************************************************************
* Unit test for discardCard()
****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include <stdio.h>
#include <string.h>
#include "rngs.h"

#define TESTNAME "updateCoins()"
#define TEST_ID_START 1 

int main() {    
    printf ("*** UNIT TEST BEGIN %s ***\n\n", TESTNAME);
    int test_num = TEST_ID_START; 
    
    int player = 0; 

    int seed = 100;
    int numPlayers = 2;
    
    int k[10] = {treasure_map, sea_hag, feast, gardens, mine
               , remodel, smithy, village, cutpurse, great_hall};

    struct gameState initialState; // a blank slate to check against and to reset nextState
    struct gameState nextState; // changes are made to nextState to trigger test results 

    initializeGame(numPlayers, k, seed, &initialState); // initialState is a blank slate 
    memcpy(&nextState, &initialState, sizeof(struct gameState)); 

    updateCoins(player, &nextState, 0);
    nextState.coins = initialState.coins; 
    assert_print(memcmp(&nextState, &initialState, sizeof(struct gameState)), 0, "Update coins only alters coins field (game state otherwise unchanged)", &test_num); 

    for(int i = 0; i < nextState.handCount[player]; i++){
        nextState.hand[player][i] = copper; 
    }

    updateCoins(player, &nextState, 0);
    assert_print(nextState.handCount[player], nextState.coins, "Full hand of coppers", &test_num); 

    for(int i = 0; i < nextState.handCount[player]; i++){
        nextState.hand[player][i] = silver; 
    }

    updateCoins(player, &nextState, 0);
    assert_print(nextState.handCount[player] * 2, nextState.coins, "Full hand of silvers", &test_num); 

    for(int i = 0; i < nextState.handCount[player]; i++){
        nextState.hand[player][i] = gold; 
    }

    updateCoins(player, &nextState, 5);
    assert_print(nextState.handCount[player] * 3 + 5, nextState.coins, "Full hand of golds and bonus", &test_num); 

    for(int i = 0; i < nextState.handCount[player]; i++){
        nextState.hand[player][i] = feast; 
    }

    updateCoins(player, &nextState, 0);
    assert_print(0, nextState.coins, "no coins", &test_num); 

    nextState.hand[player][0] = copper; 
    nextState.hand[player][2] = silver;
    nextState.hand[player][3] = gold;  
    updateCoins(player, &nextState, 0);
    assert_print(6, nextState.coins, "Mix of all coin types", &test_num); 

    nextState.handCount[player] = 0; 
    updateCoins(player, &nextState, 0);
    assert_print(0, nextState.coins, "Empty hand", &test_num);    

    printf ("\n*** UNIT TEST END %s   ***\n", TESTNAME);
    return 0;
}
