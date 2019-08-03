#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>

int main () {
	int i;
	printf("\n******************************************************************************************\n");
	printf("                                  UNIT TEST 1: Baron Card                                 \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	//Player chooses to discard estate card
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                 DISCARD ESTATE ASSERTIONS                                \n");
	printf("------------------------------------------------------------------------------------------\n");
	//Player's hand holds an estate card
	printf("ESTATE CARD IN HAND\n");
	testState.supplyCount[estate] = 10;
	testState.handCount[0] = 5;
	testState.hand[0][0] = curse;
	testState.hand[0][1] = baron;
	testState.hand[0][2] = estate;
	for (i = 3; i < 5; i++)
	{
		testState.hand[0][i] = i;
	}
	testState.numBuys = 1;
	testState.discardCount[0] = 0;
	testState.coins = 0;
	testState.whoseTurn = 0;
	baronCase(&testState, 1);
	printf("Number of buys increased by 1: ");
	asserttrue(testState.numBuys == 2, 1);
	printf("Player 1 discard pile now holds one estate card: ");
	asserttrue(testState.discard[0][0] == estate, 1);
	printf("Player 1's hand count decreased by 2: ");
	asserttrue(testState.handCount[0] == 3, 1);
	printf("Player now has one less estate card in hand: ");
	int estateCount = 0;
	for (i = 0; i < testState.handCount[0]; i++)
	{
		if (testState.hand[0][i] == estate)
		{
			estateCount += 1;
		}
	}
	asserttrue(estateCount == 3, 1);
	printf("First card in hand remains the same: ");
	asserttrue(testState.hand[0][0] == curse, 1);
	printf("Baron card is discarded from hand: ");
	asserttrue(testState.hand[0][1] != baron, 1);
	printf("Number of coins increased by 4: ");
	asserttrue(testState.coins == 4, 1);
	printf("Estate supply count remains the same: ");
	asserttrue(testState.supplyCount[estate] == 10, 1);
	//Player's hand does not hold an estate card
	printf("\nESTATE CARD NOT IN HAND\n");
	testState.supplyCount[estate] = 10;
	testState.handCount[0] = 1;
	testState.hand[0][0] = baron;
	testState.numBuys = 1;
	testState.discardCount[0] = 0;
	testState.coins = 0;
	testState.whoseTurn = 0;
	baronCase(&testState, 1);
	printf("Number of buys increased by 1: ");
	asserttrue(testState.numBuys == 2, 1);
	printf("Player 1's hand count decreases by 1: ");
	asserttrue(testState.handCount[0] == 0, 1);
	printf("Player now has one estate card in discard: ");
	estateCount = 0;
	for (i = 0; i < testState.discardCount[0]; i++)
	{
		if (testState.discard[0][i] == estate)
		{
			estateCount += 1;
		}
	}
	asserttrue(estateCount == 1, 1);
	printf("Baron is discarded from hand: ");
	asserttrue(testState.hand[0][0] != baron, 1);
	printf("Number of coins remains the same: ");
	asserttrue(testState.coins == 0, 1);
	printf("Estate supply count decreases by 1: ");
	asserttrue(testState.supplyCount[estate] == 9, 1);

	//Player chooses to gain estate card
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                   GAIN ESTATE ASSERTIONS                                 \n");
	printf("------------------------------------------------------------------------------------------\n");
	testState.supplyCount[estate] = 10;
	testState.handCount[0] = 1;
	testState.hand[0][0] = baron;
	testState.numBuys = 1;
	testState.discardCount[0] = 0;
	testState.coins = 0;
	testState.whoseTurn = 0;
	baronCase(&testState, 0);
	printf("Number of buys increased by 1: ");
	asserttrue(testState.numBuys == 2, 1);
	printf("Player 1's hand count remains the same: ");
	asserttrue(testState.handCount[0] == 1, 1);
	printf("Player now has one estate card in discard: ");
	estateCount = 0;
	for (i = 0; i < testState.discardCount[0]; i++)
	{
		if (testState.discard[0][i] == estate)
		{
			estateCount += 1;
		}
	}
	asserttrue(estateCount == 1, 1);
	printf("Baron card is discarded from hand: ");
	asserttrue(testState.hand[0][0] != baron, 1);
	printf("Number of coins remains the same: ");
	asserttrue(testState.coins == 0, 1);
	printf("Estate supply count decreases by 1: ");
	asserttrue(testState.supplyCount[estate] == 9, 1);
	printf("\n\n");
	return 0;
}
