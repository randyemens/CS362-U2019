#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>

int main () {
	int i;
	int j;
	printf("\n******************************************************************************************\n");
	printf("                               UNIT TEST 3: Ambassador Card                               \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
			 sea_hag, tribute, curse };
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                   ERROR CHECK ASSERTIONS                                 \n");
	printf("------------------------------------------------------------------------------------------\n");
	initializeGame(4, k, 30, &testState);
	testState.handCount[0] = 4;
	for (i = 0; i < 4; i++)
	{
		testState.hand[0][i] = curse;
	}
	testState.hand[0][2] = ambassador;
	testState.discardCount[0] = 0;
	testState.whoseTurn = 0;
	printf("Choice 1 cannot be equal to hand position: ");
	asserttrue(ambassadorCase(&testState, 2, 2, 3) == -1, 1);
	printf("Choice 2 cannot be greater than 2: ");
	asserttrue(ambassadorCase(&testState, 2, 0, 3) == -1, 1);
	printf("Choice 2 cannot be less than 0: ");
	asserttrue(ambassadorCase(&testState, 2, 0, -1) == -1, 1);
	printf("Choice 2 cannot be greater than the number of card type to be discarded: ");
	testState.handCount[0] = 3;
	testState.hand[0][0] = curse;
	testState.hand[0][1] = ambassador;
	testState.hand[0][2] = minion;
	testState.discardCount[0] = 0;
	testState.whoseTurn = 0;
	asserttrue(ambassadorCase(&testState, 1, 0, 2) == -1, 1);
	printf("Return value equals 0 with proper amount of card type: ");
	testState.handCount[0] = 4;
	for (i = 0; i < 4; i++)
	{
		testState.hand[0][i] = curse;
	}
	testState.hand[0][2] = ambassador;
	testState.discardCount[0] = 0;
	testState.whoseTurn = 0;
	asserttrue(ambassadorCase(&testState, 2, 0, 2) == 0, 1);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                   CARD ACTION ASSERTIONS                                 \n");
	printf("------------------------------------------------------------------------------------------\n");
	for (j = 1; j < 3; j++)
	{
		printf("\nPLAYER CHOOSES %i CARDS\n", j);
		initializeGame(4, k, 30, &testState);
		testState.handCount[0] = 4;
		for (i = 0; i < 4; i++)
		{
			testState.hand[0][i] = curse;
		}
		testState.hand[0][0] = ambassador;
		for (i = 1; i < 4; i++)
		{
			testState.handCount[i] = 0;
		}
		testState.discardCount[0] = 0;
		testState.supplyCount[curse] = 5;
		printf("Return value is 0: ");
		testState.whoseTurn = 0;
		asserttrue(ambassadorCase(&testState, 0, 3, j) == 0, 1);
		printf("Supply count decreased by (# of players - 1 - # discarded by player 1): <Result %i> ", testState.supplyCount[curse]);
		asserttrue(testState.supplyCount[curse] == 5 - testState.numPlayers - 1 - j, 1);
		printf("Every other player hand now includes a Curse card: ");
		int passed = 0;
		for (i = 1; i < 4; i++)
		{
			passed += asserttrue(testState.hand[i][0] == curse, 0);
		}
		asserttrue(passed == 0, 1);
		printf("Player 1's discard now contains an Ambassador card: ");
		asserttrue(testState.discard[0][0] == ambassador, 1);
		printf("Player 1's hand now contains %i less curse: ", j);
		int curseCount = 0;
		for (i = 0; i < testState.handCount[0]; i++)
		{
			if (testState.hand[0][i] == curse)
			{
				curseCount += 1;
			}
		}
		asserttrue(curseCount == 3 - j, 1);
	}
	printf("\n\n");
	return 0;
}
