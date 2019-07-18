#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
	int i;
	int j;
	printf("\n******************************************************************************************\n");
	printf("                                  CARD TEST 2: Shuffling                                  \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
			 sea_hag, tribute, smithy };
	initializeGame(4, k, 35, &testState);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                  ERROR CHECK ASSERTIONS                                  \n");
	printf("------------------------------------------------------------------------------------------\n");
	testState.deckCount[0] = 0;
	printf("The deck must have at least one card to shuffle: ");
	int returnValue = shuffle(0, &testState);
	asserttrue(returnValue == -1, 1);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                    SHUFFLE ASSERTIONS                                    \n");
	printf("------------------------------------------------------------------------------------------\n");
	//Initialize Player 1-4's decks
	for (i = 0; i < 4; i++)
	{
		testState.deckCount[i] = 10;
	}
	int cardCount[26]; //Array to keep track of number of each card type in player deck
	int playerDeckCheck[4][10];
	for (i = 0; i < testState.deckCount[0]; i++)
	{
		for (j = 0; j < 4; j++)
		{
			testState.deck[j][i] = rand() % 27;
			playerDeckCheck[j][i] = testState.deck[j][i];
		}
		cardCount[testState.deck[0][i]] += 1;
	}
	shuffle(0, &testState);
	printf("Deck must have same amount of each card type before and after shuffling: ");
	for (i = 0; i < testState.deckCount[0]; i++)
	{
		cardCount[testState.deck[0][i]] -= 1;
	}
	int passed = 0;
	for (i = 0; i < 27; i++)
	{
		passed += asserttrue(cardCount[testState.deck[0][i]] == 0, 0);
	}
	asserttrue(passed == 0, 1);
	passed = 0;
	printf("First player deck should change: ");
	for (i = 0; i < 10; i++)
	{
		passed += asserttrue(testState.deck[0][i] == playerDeckCheck[0][i], 0);
	}
	asserttrue(passed > 0, 1);
	passed = 0;
	printf("Rest of player decks should not change: ");
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < 10; j++)
		{
			passed += asserttrue(testState.deck[i][j] == playerDeckCheck[i][j], 0);
		}
	}
	asserttrue(passed == 0, 1);
	printf("\n\n");
	return 0;
}