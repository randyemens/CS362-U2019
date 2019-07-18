#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
	int i;
	int j;
	printf("\n******************************************************************************************\n");
	printf("                                   CARD TEST 3: End Turn                                  \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
			 sea_hag, tribute, smithy };
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                 PLAYER CHANGE ASSERTIONS                                 \n");
	printf("------------------------------------------------------------------------------------------\n");
	initializeGame(4, k, 35, &testState);
	testState.whoseTurn = 2;
	endTurn(&testState);
	printf("Current player updates from 2 to 3: ");
	asserttrue(whoseTurn(&testState) == 3, 1);
	endTurn(&testState);
	printf("Current player updates from 3 to 0: ");
	asserttrue(whoseTurn(&testState) == 0, 1);
	endTurn(&testState);
	printf("Current player updates from 0 to 1: ");
	asserttrue(whoseTurn(&testState) == 1, 1);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                     STATE ASSERTIONS                                     \n");
	printf("------------------------------------------------------------------------------------------\n");
	initializeGame(4, k, 35, &testState);
	testState.outpostPlayed = 5;
	testState.phase = 3;
	testState.numActions = 0;
	testState.coins = 1;
	testState.numBuys = 0;
	testState.playedCardCount = 4;
	testState.handCount[1] = 4;
	endTurn(&testState);
	printf("Game state outpostPlayed variable is set to 0: ");
	asserttrue(testState.outpostPlayed == 0, 1);
	printf("Game state phase variable is set to 0: ");
	asserttrue(testState.phase == 0, 1);
	printf("Game state numActions variable is set to 1: ");
	asserttrue(testState.numActions == 1, 1);
	printf("Game state coins variable is set to 0: ");
	asserttrue(testState.coins == 0, 1);
	printf("Game state numBuys variable is set to 1: ");
	asserttrue(testState.numBuys == 1, 1);
	printf("Game state playedCardCount variable is set to 0: ");
	asserttrue(testState.playedCardCount == 0, 1);
	printf("Next Player's game state handCount variable is unchanged: ");
	asserttrue(testState.handCount[1] == 4, 1);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                  PLAYER HAND ASSERTIONS                                  \n");
	printf("------------------------------------------------------------------------------------------\n");
	initializeGame(4, k, 35, &testState);
	//Initialize Player 1-4's decks
	for (i = 0; i < 4; i++)
	{
		testState.deckCount[i] = 10;
		for (j = 0; j < 10; j++)
		{
			testState.deck[i][j] = j;
		}
	}
	//Initialize Player 1-4's hands
	int playerHandCheck[4][10]; //Array is used to hold hand info before endTurn is called
	//Initialize Player 1's hand to two cards
	testState.handCount[0] = 2;
	for (i = 0; i < 2; i++)
	{
		testState.hand[0][i] = i + 1;
		playerHandCheck[0][i] = i + 1;
	}
	//Initialize every other player hand to five cards
	for (i = 1; i < 4; i++)
	{
		testState.handCount[i] = 5;
		for (j = 0; j < testState.handCount[i]; j++)
		{
			testState.hand[i][j] = j + 1;
			playerHandCheck[i][j] = j + 1;
		}
	}
	//Initialize Player 1's discard to two cards (1 and 2)
	testState.discardCount[0] = 2;
	for (i = 1; i < 3; i++)
	{
		testState.discard[0][i - 1] = i;
	}
	//First call to endTurn
	endTurn(&testState);
	printf("FIRST CALL TO ENDTURN\n");
	printf("Player 1's discard pile should have 4 cards (2 existing + 2 new): ");
	asserttrue(testState.discardCount[0] == 4, 1);
	printf("Player 1's previous hand should be at the top of the discard pile: ");
	int passed = 0;
	for (i = 1; i < 3; i++)
	{
		passed += asserttrue(testState.discard[0][i + 1] == i, 0); //Check if discard has 1 and 2 at index 2 and 3
	}
	asserttrue(passed == 0, 1);
	printf("Player 1's hand now has 5 cards: ");
	asserttrue(testState.handCount[0] == 5, 1);
	printf("Player 1 drew 5 cards from top of deck: ");
	asserttrue(testState.deckCount[0] == 5, 1);
	printf("Every other player's hand remains the same: ");
	passed = 0;
	for (i = 1; i < 4; i++)
	{
		testState.handCount[i] = 5;
		for (j = 0; j < testState.handCount[i]; j++)
		{
			passed += asserttrue(testState.hand[i][j] == playerHandCheck[i][j], 0);
		}
	}
	asserttrue(passed == 0, 1);
	printf("\n\n");
	return 0;
}