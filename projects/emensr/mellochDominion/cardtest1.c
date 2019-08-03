#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>

void SupplyCheck(int playerCount, struct gameState testState, int k[])
{
	int i;
	printf("\nSUPPLY DECKS COUNT TESTS\n");
	int supplyCountCheck[treasure_map + 1]; //Array for if supply card is in play
	for (i = 0; i <= treasure_map; i++) //Set array values to 0
	{
		supplyCountCheck[i] = 0;
	}
	//CURSE CARD CHECK
	int numCurse;
	if (playerCount == 2) { numCurse = 10; }
	else if (playerCount == 3) { numCurse = 20; }
	else { numCurse = 30; }
	printf("Number of Curse cards is %i: ", numCurse);
	asserttrue(testState.supplyCount[curse] == numCurse, 1);
	supplyCountCheck[curse] = 1;
	//VICTORY CARD CHECK
	int numVictory;
	if (playerCount == 2) { numVictory = 8; }
	else  { numVictory = 12; }
	//Estate
	printf("Number of Estate cards is %i: ", numVictory);
	asserttrue(testState.supplyCount[estate] == numVictory, 1);
	supplyCountCheck[estate] = 1;
	//Duchy
	printf("Number of Duchy cards is %i: ", numVictory);
	asserttrue(testState.supplyCount[duchy] == numVictory, 1);
	supplyCountCheck[duchy] = 1;
	//Province
	printf("Number of Province cards is %i: ", numVictory);
	asserttrue(testState.supplyCount[province] == numVictory, 1);
	supplyCountCheck[province] = 1;
	//TREASURE CARD CHECK
	//Copper
	printf("Number of Copper cards is %i: ", 60 - 7 * playerCount);
	asserttrue(testState.supplyCount[copper] == 60 - 7 * playerCount, 1);
	supplyCountCheck[copper] = 1;
	//Silver
	printf("Number of Silver cards is 40: ");
	asserttrue(testState.supplyCount[silver] == 40, 1);
	supplyCountCheck[silver] = 1;
	//Gold
	printf("Number of Gold cards is 30: ");
	asserttrue(testState.supplyCount[gold] == 30, 1);
	supplyCountCheck[gold] = 1;
	//KINGDOM CARDS
	//Chosen Kingdom Cards
	int numKingdom;
	if (playerCount == 2) { numKingdom = 8; }
	else { numKingdom = 12; }
	printf("Number of each chosen Kingdom card is 10 (or %i for Great Hall/Gardens): ", numKingdom);
	int passed = 0;
	for (i = 0; i < 10; i++)
	{
		if (k[i] == great_hall || k[i] == gardens)
		{
			passed += asserttrue(testState.supplyCount[k[i]] == numKingdom, 0);
		}
		else
		{
			passed += asserttrue(testState.supplyCount[k[i]] == 10, 0);
		}
		supplyCountCheck[k[i]] = 1;
	}
	asserttrue(passed == 0, 1);
	printf("Number for each non-chosen Kingdom card is set to -1: ");
	passed = 0;
	for (i = 0; i <= treasure_map; i++)
	{
		if (supplyCountCheck[i] == 0)
		{
			passed += asserttrue(testState.supplyCount[i] == -1, 0);
		}
	}
	asserttrue(passed == 0, 1);
}

void DeckCheck(int playerCount, struct gameState testState)
{
	printf("\nPLAYER DECK TEST\n");
	int i;
	int j;
	int supplyCountCheck[treasure_map + 1];
	printf("Each player deck has 3 Estate and 7 Copper Cards: ");
	int passed = 0;
	for (i = 0; i < playerCount; i++)
	{
		for (j = 0; j <= treasure_map; j++)
		{
			supplyCountCheck[j] = 0;
		}
		for (j = 0; j < testState.deckCount[i]; j++)
		{
			supplyCountCheck[testState.deck[i][j]] += 1;
		}
		if (i == 0)
		{
			for (j = 0; j < testState.handCount[0]; j++)
			{
				supplyCountCheck[testState.hand[i][j]] += 1;
			}
		}
		for (j = 0; j <= treasure_map; j++)
		{
			if (j == estate)
			{
				passed += asserttrue(supplyCountCheck[j] == 3, 0);
			}
			else if (j == copper)
			{
				passed += asserttrue(supplyCountCheck[j] == 7, 0);
			}
			else
			{
				passed += asserttrue(supplyCountCheck[j] == 0, 0);
			}
		}
	}
	asserttrue(passed == 0, 1);
}

void HandCheck(int playerCount, struct gameState testState)
{
	printf("\nPLAYER HAND TEST\n");
	printf("Every player draws five cards before the start of the game: ");
	int passed = 0;
	int i;
	for (i = 0; i < playerCount; i++)
	{
			passed += asserttrue(testState.handCount[i] == 5, 0);
	}
	asserttrue(passed == 0, 1);
	printf("Every player deck is now at five cards: ");
	passed = 0;
	for (i = 0; i < playerCount; i++)
	{
		passed += asserttrue(testState.deckCount[i] == 5, 0);
	}
	asserttrue(passed == 0, 1);
}

int main () {
	printf("\n******************************************************************************************\n");
	printf("                             CARD TEST 1: Game Initialization                             \n");
	printf("******************************************************************************************\n");
	int returnValue;
	struct gameState testState;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
			 sea_hag, tribute, smithy };
	//ERROR CHECKING
	//Assertion for minimum number of player check
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                  ERROR CHECK ASSERTIONS                                  \n");
	printf("------------------------------------------------------------------------------------------\n");
	printf("Number of players cannot be less than 2: ");
	returnValue = initializeGame(1, k, 30, &testState);
	asserttrue(returnValue == -1, 1);
	//Assertion for maximum number of player check
	printf("Number of players cannot be greater than %i: ", MAX_PLAYERS);
	returnValue = initializeGame(5, k, 30, &testState);
	asserttrue(returnValue == -1, 1);
	//Assertion for different kingdom check
	k[9] = adventurer;
	printf("Kingdom card types must all be different: ");
	returnValue = initializeGame(2, k, 30, &testState);
	asserttrue(returnValue == -1, 1);
	k[9] = smithy;

	//PLAYER COUNT SPECIFIC CHECKS
	int i;
	for (i = 2; i < 5; i++)
	{
		printf("\n\n------------------------------------------------------------------------------------------\n");
		printf("                           %i PLAYERED INITIALIZATION ASSERTIONS                           \n", i);
		printf("------------------------------------------------------------------------------------------\n");
		returnValue = initializeGame(i, k, 30, &testState);
		printf("Initialization return value is 0 for correct input values: ");
		asserttrue(returnValue == 0, 1);
		SupplyCheck(i, testState, k);
		DeckCheck(i, testState);
		HandCheck(i, testState);
	}
	printf("\n\n");
	return 0;
}
