#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>

int main () {
	int i;
	printf("\n******************************************************************************************\n");
	printf("                                  UNIT TEST 5: Mine Card                                  \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
	 sea_hag, tribute, curse };
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                  ERROR CHECK ASSERTIONS                                  \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("Trash choice below 4 returns -1: ");
	initializeGame(4, k, 30, &testState);
	testState.handCount[0] = 2;
	testState.hand[0][0] = curse;
	testState.hand[0][1] = mine;
	asserttrue(mineCard(0, 4, &testState, 0, 1) == -1, 1);
	printf("Trash choice above 6 returns -1: ");
	initializeGame(4, k, 30, &testState);
	testState.handCount[0] = 2;
	testState.hand[0][0] = embargo;
	testState.hand[0][1] = mine;
	asserttrue(mineCard(0, 4, &testState, 0, 1) == -1, 1);
	printf("Choice2 below 4 returns -1: ");
	initializeGame(4, k, 30, &testState);
	testState.handCount[0] = 2;
	testState.hand[0][0] = gold;
	testState.hand[0][1] = mine;
	asserttrue(mineCard(0, 3, &testState, 0, 1) == -1, 1);
	printf("Choice2 above 6 returns -1: ");
	initializeGame(4, k, 30, &testState);
	testState.handCount[0] = 2;
	testState.hand[0][0] = gold;
	testState.hand[0][1] = mine;
	asserttrue(mineCard(0, 7, &testState, 0, 1) == -1, 1);
	printf("Choosing card that is over +3 cost returns -1: ");
	initializeGame(4, k, 30, &testState);
	testState.handCount[0] = 2;
	testState.hand[0][0] = 4;
	testState.hand[0][1] = mine;
	asserttrue(mineCard(0, 6, &testState, 0, 1) == -1, 1);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                  CARD ACTION ASSERTIONS                                  \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("REPLACING COPPER WITH SILVER\n");
	initializeGame(4, k, 30, &testState);
	testState.handCount[0] = 2;
	testState.hand[0][0] = mine;
	testState.hand[0][1] = copper;
	printf("Return value is 0: ");
	asserttrue(mineCard(1, silver, &testState, 0, 0) == 0, 1);
	printf("Hand now holds silver: ");
	int passed = 0;
	for (i = 0; i < testState.handCount[0]; i++)
	{
		if (testState.hand[0][i] == silver)
		{
			passed = 1;
		}
	}
	asserttrue(passed == 1, 1);
	printf("Copper is not in discard: ");
	passed = 1;
	for (i = 0; i < testState.discardCount[0]; i++)
	{
		if (testState.discard[0][i] == copper)
		{
			passed = 0;
		}
	}
	asserttrue(passed == 1, 1);
	printf("\n\n");
	return 0;
}
