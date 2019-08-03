#include "dominion.h"
#include "dominion_helpers.h"
#include "asserttrue.h"
#include <stdio.h>

int main () {
	int i;
	int j;
	printf("\n******************************************************************************************\n");
	printf("                                  CARD TEST 5: Draw Card                                  \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	//TEST WITH 5 CARDS IN DECK
	//Initialize players' hand, deck, and discard
	testState.numPlayers = 4;
	for (i = 0; i < 4; i++)
	{
		testState.handCount[i] = 5;
		testState.deckCount[i] = 5;
		testState.discardCount[i] = 5;
		for (j = 0; j < 5; j++)
		{
			testState.hand[i][j] = j;
			testState.deck[i][j] = j;
			testState.discard[i][j] = j;
		}
	}
	//Draw deck and check values
	printf("PLAYER 1 DRAWS WITH 5 CARDS IN DECK\n");
	drawCard(0, &testState);
	printf("Player 1's hand holds 6 cards: ");
	asserttrue(testState.handCount[0] == 6, 1);
	printf("Player 1's last card is a 4: ");
	asserttrue(testState.hand[0][testState.handCount[0] - 1] == 4, 1);
	printf("Player 1's deck holds 4 cards: ");
	asserttrue(testState.deckCount[0] == 4, 1);
	printf("Player 1's discard holds 5 cards: ");
	asserttrue(testState.discardCount[0] == 5, 1);
	printf("Every other player's hand, deck, and discard remains the same: ");
	int passed = 0;
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < 5; j++)
		{
			passed += asserttrue(testState.handCount[i] == 5, 0);
			passed += asserttrue(testState.deckCount[i] == 5, 0);
			passed += asserttrue(testState.discardCount[i] == 5, 0);
		}
	}
	asserttrue(passed == 0, 1);
	//TEST WITH NO REMAINING CARDS IN DECK
	//Initialize players' hand, deck, and discard
	for (i = 0; i < 4; i++)
	{
		testState.handCount[i] = 5;
		testState.deckCount[i] = 5;
		testState.discardCount[i] = 5;
		for (j = 0; j < 5; j++)
		{
			testState.hand[i][j] = j;
			testState.deck[i][j] = j;
			testState.discard[i][j] = j;
		}
	}
	testState.deckCount[0] = 0;
	//Draw deck and check values
	printf("\nPLAYER 1 DRAWS WITH 0 CARDS IN DECK\n");
	drawCard(0, &testState);
	printf("Player 1's hand holds 6 cards: ");
	asserttrue(testState.handCount[0] == 6, 1);
	printf("Player 1's deck holds 4 cards: ");
	asserttrue(testState.deckCount[0] == 4, 1);
	printf("Player 1's discard holds 0 cards: ");
	asserttrue(testState.discardCount[0] == 0, 1);
	printf("Every other player's hand, deck, and discard remains the same: ");
	passed = 0;
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < 5; j++)
		{
			passed += asserttrue(testState.handCount[i] == 5, 0);
			passed += asserttrue(testState.deckCount[i] == 5, 0);
			passed += asserttrue(testState.discardCount[i] == 5, 0);
		}
	}
	asserttrue(passed == 0, 1);
	printf("\n\n");
	return 0;
}
