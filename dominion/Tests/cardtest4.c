#include "dominion.h"
#include "asserttrue.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

void resetCards(struct gameState *testState)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		testState->handCount[i] = 0;
		testState->discardCount[i] = 0;
		testState->deckCount[i] = 0;
	}
}

int getVictoryPoints(int card)
{
	if (card == curse) { return -1; };
	if (card == estate) { return 1; };
	if (card == duchy) { return 3; };
	if (card == province) { return 6; };
	if (card == great_hall) { return 1; };
	return 0;
}

int main () {
	int i;
	printf("\n******************************************************************************************\n");
	printf("                               CARD TEST 4: Getting Winners                               \n");
	printf("******************************************************************************************\n");
	struct gameState testState;
	int players[MAX_PLAYERS];
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("                                 PLAYER SCORES ASSERTIONS                                 \n");
	printf("------------------------------------------------------------------------------------------\n");
	resetCards(&testState);
	testState.handCount[0] = 1;
	testState.discardCount[1] = 1;
	testState.deckCount[2] = 1;
	for (i = 0; i < 4; i++)
	{
		char cardName[16];
		cardNumToName(i, cardName);
		printf("TEST %s CARD\n", cardName);
		//Test Hand Score
		testState.hand[0][0] = i;
		printf("Score from hand is %i: ", getVictoryPoints(i));
		asserttrue(scoreFor(0, &testState) == getVictoryPoints(i), 1);
		//Test Discard Score
		testState.discard[1][0] = i;
		printf("Score from discard is %i: ", getVictoryPoints(i));
		asserttrue(scoreFor(1, &testState) == getVictoryPoints(i), 1);
		//Test Deck Score
		testState.deck[2][0] = i;
		printf("Score from deck is %i: ", getVictoryPoints(i));
		asserttrue(scoreFor(2, &testState) == getVictoryPoints(i), 1);
		printf("\n");
	}
	printf("------------------------------------------------------------------------------------------\n");
	printf("                                     WINNER ASSERTIONS                                    \n");
	printf("------------------------------------------------------------------------------------------\n");
	resetCards(&testState);
	testState.numPlayers = 2;
	testState.whoseTurn = 1;
	printf("2 PLAYERED TIE\n");
	getWinners(players, &testState);
	printf("Player 1 must equal 1: ");
	asserttrue(players[0] == 1, 1);
	printf("Player 2 must equal 1: ");
	asserttrue(players[1] == 1, 1);
	printf("Player 3 must equal 0: ");
	asserttrue(players[2] == 0, 1);
	printf("Player 4 must equal 0: ");
	asserttrue(players[3] == 0, 1);
	testState.whoseTurn = 0;
	printf("\n2 PLAYERED TIE-BREAKER\n");
	printf("Only Player 2 equals 1: ");
	getWinners(players, &testState);
	int passed = 0;
	for (i = 0; i < 4; i++)
	{
		if (i == 1)
		{
			passed += asserttrue(players[i] == 1, 0);
		}
		else
		{
			passed += asserttrue(players[i] == 0, 0);
		}
	}
	asserttrue(passed == 0, 1);
	printf("\n\n");
	return 0;
}