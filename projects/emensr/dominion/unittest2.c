#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>

int main () {
	int i;
	int j;
	printf("\n******************************************************************************************\n");
	printf("                                 UNIT TEST 2: Minion Card                                 \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
			 sea_hag, tribute, smithy };
	//Player chooses to gain two coins
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                    +2 COINS ASSERTIONS                                   \n");
	printf("------------------------------------------------------------------------------------------\n");
	initializeGame(4, k, 30, &testState);
	for (i = 0; i < 4; i++)
	{
		testState.handCount[i] = 4;
		for (j = 0; j < 4; j++)
		{
			testState.hand[i][j] = j;
		}
		testState.deckCount[i] = 4;
		for (j = 0; j < 4; j++)
		{
			testState.deck[i][j] = j + 5;
		}
	}
	testState.hand[0][2] = minion;
	testState.numActions = 1;
	testState.discardCount[0] = 0;
	testState.coins = 0;
	minionCard(1, 0, &testState, 0, 2);
	printf("Number of actions increased by 1: ");
	asserttrue(testState.numActions == 2, 1);
	printf("Number of coins increased by 2: ");
	asserttrue(testState.coins == 2, 1);
	printf("Minion card is discarded from hand: ");
	asserttrue(testState.hand[0][2] != minion, 1);
	printf("Player 1's hand decreased by 1 (from discarding minion): ");
	asserttrue(testState.handCount[0] == 3, 1);
	printf("Minion card is now in playedCards array: ");
	asserttrue(testState.playedCards[0] == minion, 1);
	printf("Every other player's hand count remains the same: ");
	int passed = 0;
	for (i = 1; i < 4; i++)
	{
		passed += asserttrue(testState.handCount[i] == 4, 0);
	}
	asserttrue(passed == 0, 1);
	printf("Every player's deck count remains the same: ");
	passed = 0;
	for (i = 1; i < 4; i++)
	{
		passed += asserttrue(testState.deckCount[i] == 4, 0);
	}
	asserttrue(passed == 0, 1);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                   REDRAW HAND ASSERTIONS                                 \n");
	printf("------------------------------------------------------------------------------------------\n");
	initializeGame(4, k, 30, &testState);
	for (i = 0; i < 4; i++)
	{
		testState.handCount[i] = i + 2;
		for (j = 0; j < 4; j++)
		{
			testState.hand[i][j] = j;
		}
		testState.deckCount[i] = 4;
		for (j = 0; j < 4; j++)
		{
			testState.deck[i][j] = j + 5;
		}
	}
	testState.hand[0][0] = minion;
	testState.numActions = 1;
	testState.discardCount[0] = 0;
	testState.coins = 0;
	minionCard(0, 1, &testState, 0, 2);
	printf("Number of actions increased by 1: ");
	asserttrue(testState.numActions == 2, 1);
	printf("\nPLAYER 1 ASSERTIONS (initialized to 2 cards in hand, 4 cards in deck, 0 cards in discard)\n");
	printf("Player 1 should have 4 cards in hand: <Result = %i> ", testState.handCount[0]);
	asserttrue(testState.handCount[0] == 4, 1);
	printf("Player 1 should have 0 cards in deck: <Result = %i> ", testState.deckCount[0]);
	asserttrue(testState.deckCount[0] == 0, 1);
	printf("Player 1 should have 2 cards in discard: <Result = %i> ", testState.discardCount[0]);
	asserttrue(testState.discardCount[0] == 2, 1);
	printf("\nPLAYER 2 ASSERTIONS (initialized to 3 cards in hand, 4 cards in deck, 0 cards in discard)\n");
	printf("Player 2 should have 3 cards in hand: <Result = %i> ", testState.handCount[1]);
	asserttrue(testState.handCount[1] == 3, 1);
	printf("Player 2 should have 4 cards in deck: <Result = %i> ", testState.deckCount[1]);
	asserttrue(testState.deckCount[1] == 4, 1);
	printf("Player 2 should have 0 cards in discard: <Result = %i> ", testState.discardCount[1]);
	asserttrue(testState.discardCount[1] == 0, 1);
	printf("\nPLAYER 3 ASSERTIONS (initialized to 4 cards in hand, 4 cards in deck, 0 cards in discard)\n");
	printf("Player 3 should have 4 cards in hand: <Result = %i> ", testState.handCount[2]);
	asserttrue(testState.handCount[2] == 4, 1);
	printf("Player 3 should have 4 cards in deck: <Result = %i> ", testState.deckCount[2]);
	asserttrue(testState.deckCount[2] == 4, 1);
	printf("Player 3 should have 0 cards in discard: <Result = %i> ", testState.discardCount[2]);
	asserttrue(testState.discardCount[2] == 0, 1);
	printf("\nPLAYER 4 ASSERTIONS (initialized to 5 cards in hand, 4 cards in deck, 0 cards in discard)\n");
	printf("Player 4 should have 4 cards in hand: <Result = %i> ", testState.handCount[3]);
	asserttrue(testState.handCount[3] == 4, 1);
	printf("Player 4 should have 0 cards in deck: <Result = %i> ", testState.deckCount[3]);
	asserttrue(testState.deckCount[3] == 0, 1);
	printf("Player 4 should have 5 cards in discard: <Result = %i> ", testState.discardCount[3]);
	asserttrue(testState.discardCount[3] == 5, 1);
	printf("\n\n");
	return 0;
}
