#include "dominion.h"
#include "dominion_helpers.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int initRandTributeState(struct gameState *state, int showTests) {
	if (showTests == 1) { printf("-------------------------------------INITIALIZE-------------------------------------\n"); }
	int i;
	int j;
	//RANDOM NUMBER OF PLAYERS FROM 2-4
	state->numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
	if (showTests == 1) { printf("INITIALIZATION VALUES\nNUMBER OF PLAYERS: %i\n", state->numPlayers); }
	//RANDOM NUMBER OF CURSES
	if (state->numPlayers == 2) {
		state->supplyCount[curse] = rand() % 11;
	}
	else if (state->numPlayers == 3) {
		state->supplyCount[curse] = rand() % 21;
	}
	else {
		state->supplyCount[curse] = rand() % 31;
	}
	state->supplyCount[copper] = rand() % 61;
	state->supplyCount[silver] = rand() % 41;
	state->supplyCount[gold] = rand() % 31;
	//RANDOM NUMBER OF ESTATE-PROVINCE
	for (i = estate; i <= province; i++) {
		if (state->numPlayers == 2) {
			state->supplyCount[i] = rand() % 9;
		}
		else {
			state->supplyCount[i] = rand() % 13;
		}
	}
	//INITIALIZE RANDOM KINGDOM CARDS (MUST HAVE TRIBUTE)
	int kingdomCard[treasure_map + 1] = { 0 };
	kingdomCard[tribute] = 1;
	for (i = 0; i < 9; i++)  {
		int nextKingdomChoice = rand() % (treasure_map - adventurer + 1) + adventurer;
		while (kingdomCard[nextKingdomChoice] == 1) {
			nextKingdomChoice++;
			if (nextKingdomChoice > treasure_map) {
				nextKingdomChoice = adventurer;
			}
		}
		kingdomCard[nextKingdomChoice] = 1;
	}
	for (i = adventurer; i <= treasure_map; i++) {
		if (kingdomCard[i] == 1) {
			state->supplyCount[i] = rand() % 11;
		}
	}
	if (showTests == 1) { 
		printf("CARD COUNT:\n");
		for (i = 0; i <= treasure_map; i++) {
			printf("<%i: %i>\n", i, state->supplyCount[i]);
		}
	}
	state->whoseTurn = rand() % (state->numPlayers);
	if (showTests == 1) { printf("WHOSE TURN: %i\n", state->whoseTurn); }
	state->phase = rand() % 501;
	if (showTests == 1) { printf("PHASE: %i\n", state->phase); }
	state->numActions = rand() % 501;
	if (showTests == 1) { printf("NUMBER OF ACTIONS: %i\n", state->numActions); }
	state->coins = rand() % 501;
	if (showTests == 1) { printf("COINS: %i\n", state->coins); }
	state->numBuys = rand() % 501;
	if (showTests == 1) { printf("NUMBER OF BUYS: %i\n", state->numBuys); }
	int tributeIndex;
	for (i = 0; i < state->numPlayers; i++) {
		//CHOOSE LARGE OR SMALL HAND SIZE
		int size = rand() % 2;
		if (size == 0) { 
			if (state->whoseTurn == i) {
				state->handCount[i] = rand() % 10 + 1;
			}
			else {
				state->handCount[i] = rand() % 11;
			}
		}
		else { state->handCount[i] = rand() % (MAX_HAND - 1) + 1; }
		//CHOOSE LARGE OR SMALL DECK SIZE
		size = rand() % 2;
		if (size == 0) { state->deckCount[i] = rand() % 11; }
		else { state->deckCount[i] = rand() % MAX_DECK + 1; }
		//CHOOSE LARGE OR SMALL DISCARD SIZE
		size = rand() % 2;
		if (size == 0) { state->discardCount[i] = rand() % 11; }
		else { state->discardCount[i] = rand() % (MAX_DECK + 1) - state->deckCount[i]; }
		if (showTests == 1) { printf("PLAYER %i HAND:", i); }
		//CREATE HAND
		if (i == state->whoseTurn) { tributeIndex = rand() % (state->handCount[state->whoseTurn]); }
		for (j = 0; j < state->handCount[i]; j++) {
			state->hand[i][j] = rand() % (treasure_map + 1);
			if (j == tributeIndex) { state->hand[state->whoseTurn][j] = tribute; }
			if (showTests == 1) { printf("<%i>", state->hand[i][j]); }
		}
		if (showTests == 1) { printf("\n"); }
		if (showTests == 1) { printf("PLAYER %i DECK:", i); }
		//CREATE DECK
		for (j = 0; j < state->deckCount[i]; j++) {
			state->deck[i][j] = rand() % (treasure_map + 1);
			if (showTests == 1) { printf("<%i>", state->deck[i][j]); }
		}
		if (showTests == 1) { printf("\n"); }
		if (showTests == 1) { printf("PLAYER %i DISCARD:", i); }
		//CREATE DISCARD
		for (j = 0; j < state->discardCount[i]; j++) {
			state->discard[i][j] = rand() % (treasure_map + 1);
			if (showTests == 1) { printf("<%i>", state->discard[i][j]); }
		}
		if (showTests == 1) { printf("\n"); }
	}
	state->playedCardCount = rand() % (MAX_DECK + 1);
	for (j = 0; j < state->playedCardCount; j++) {
		state->playedCards[j] = rand() % (treasure_map + 1);
	}
	return tributeIndex;
}

int checkTest(struct gameState *testState, struct gameState *runState, int expectedPlayerCards[MAX_PLAYERS][treasure_map + 1], int showTests) {
	if (showTests == 1) { printf("-------------------------------------RUN CHECKS-------------------------------------\n"); }
	int i;
	int j;
	int passed = 0;
	//CHECK SUPPLY COUNT
	if (showTests == 1) { printf("SUPPLY COUNTS <#: Expected value, Calculated value>:\n"); }
	for (i = 0; i <= treasure_map; i++) {
		if (showTests == 1) { printf("<%i: %i, %i>", i, testState->supplyCount[i], runState->supplyCount[i]); }
		passed += asserttrue(testState->supplyCount[i] == runState->supplyCount[i], showTests);
	}
	//CHECK NUMBER OF ACTIONS
	if (showTests == 1) { printf("Number of actions: <Expected: %i, Calculated: %i>\n", testState->numActions, runState->numActions); }
	passed += asserttrue(testState->numActions == runState->numActions, showTests);
	//CHECK COINS
	if (showTests == 1) { printf("Number of coins: <Expected: %i, Calculated: %i>\n", testState->coins, runState->coins); }
	passed += asserttrue(testState->coins == runState->coins, showTests);
	//CHECK NUMBER OF BUYS
	if (showTests == 1) { printf("Number of buys: <Expected: %i, Calculated: %i>\n", testState->numBuys, runState->numBuys); }
	passed += asserttrue(testState->numBuys == runState->numBuys, showTests);
	//CHECK PLAYER HAND, DECK, DISCARD COUNTS
	for (j = 0; j < testState->numPlayers; j++) {
		if (showTests == 1) { printf("PLAYER %i\n", j); }
		if (showTests == 1) { printf("Hand Count: <Expected: %i, Calculated: %i>\n", testState->handCount[j], runState->handCount[j]); }
		passed += asserttrue(testState->handCount[j] == runState->handCount[j], showTests);
		if (showTests == 1) { printf("Deck Count: <Expected: %i, Calculated: %i>\n", testState->deckCount[j], runState->deckCount[j]); }
		passed += asserttrue(testState->deckCount[j] == runState->deckCount[j], showTests);
		if (showTests == 1) { printf("Discard Count: <Expected: %i, Calculated: %i>\n", testState->discardCount[j], runState->discardCount[j]); }
		passed += asserttrue(testState->discardCount[j] == runState->discardCount[j], showTests);
	}
	//CHECK PLAYER CARDS
	int runPlayerCards[MAX_PLAYERS][treasure_map + 1] = { { 0 } };
	for (j = 0; j < runState->numPlayers; j++) {
		for (i = 0; i < runState->handCount[j]; i++) {
			runPlayerCards[j][runState->hand[j][i]]++;
		}
		for (i = 0; i < runState->deckCount[j]; i++) {
			runPlayerCards[j][runState->deck[j][i]]++;
		}
		for (i = 0; i < runState->discardCount[j]; i++) {
			runPlayerCards[j][runState->discard[j][i]]++;
		}
	}
	if (showTests == 1) { printf("Number of each card type in hand <#: Expected value, Calculated value>:\n"); }
	for (j = 0; j < 4; j++) {
		if (showTests == 1) { printf("PLAYER %i:\n", j); }
		for (i = 0; i <= treasure_map; i++) {
			if (showTests == 1) { printf("<%i: %i, %i>", i, expectedPlayerCards[j][i], runPlayerCards[j][i]); }
			passed += asserttrue(expectedPlayerCards[j][i] == runPlayerCards[j][i], showTests);
		}
	}
	return passed;
}

int main () {
	time_t t;
	srand((unsigned)time(&t));
	int i;
	int j;
	int k;
	int showTests = 0;
	printf("\n******************************************************************************************\n");
	printf("                                 RANDOM TEST 3: Tribute Card                                 \n");
	printf("******************************************************************************************\n");
	
	struct gameState testState;
	struct gameState runState;
	int tributeIndex;
	int totalFailed = 0;
	for (j = 0; j < 10000; j++) {
		//printf("<%i>", j + 1);
		if (showTests == 1) { printf("--------------------------------------TEST %i--------------------------------------\n", j + 1); }
		tributeIndex = initRandTributeState(&runState, showTests);
		memcpy(&testState, &runState, sizeof(struct gameState));
		int currentPlayer = runState.whoseTurn;
		int nextPlayer = currentPlayer + 1;
		if (nextPlayer > 3) {
			nextPlayer = 0;
		}
		tributeCard(&runState, currentPlayer, nextPlayer);
		int playerCards[MAX_PLAYERS][treasure_map + 1] = { { 0 } };
		for (i = 0; i < testState.numPlayers; i++) {
			for (k = 0; k < testState.handCount[i]; k++) {
				playerCards[i][testState.hand[i][k]]++;
			}
			for (k = 0; k < testState.deckCount[i]; k++) {
				playerCards[i][testState.deck[i][k]]++;
			}
			for (k = 0; k < testState.discardCount[i]; k++) {
				playerCards[i][testState.discard[i][k]]++;
			}
		}
		//REMOVE TRIBUTE CARD
		for (i = tributeIndex; i < testState.handCount[currentPlayer] - 1; i++) {
			testState.hand[currentPlayer][i] = testState.hand[currentPlayer][i + 1];
		}
		testState.handCount[currentPlayer]--;
		testState.discard[currentPlayer][testState.discardCount[currentPlayer]] = tribute;
		testState.discardCount[currentPlayer]++;
		//UPDATE DECK COUNTS
		if (testState.deckCount[nextPlayer] >= 2) {
			testState.discardCount[nextPlayer] += 2;
			testState.deckCount[nextPlayer] -= 2;
		}
		else if (testState.deckCount[nextPlayer] + testState.discardCount[nextPlayer] >= 2) {
			testState.deckCount[nextPlayer] = testState.deckCount[nextPlayer] + testState.discardCount[nextPlayer] - 2;
			testState.discardCount[nextPlayer] += 2;
		}
		else {
			testState.deckCount[nextPlayer] = 0;
			testState.discardCount[nextPlayer] = 1;
		}
		//GET TRIBUTE CARD VALUES AT TOP OF NEXT PLAYER DISCARD
		int tributes[2] = { -1, -1 };
		if (testState.discardCount[nextPlayer] >= 1) { tributes[0] = testState.discard[nextPlayer][0]; }
		if (testState.discardCount[nextPlayer] >= 2) { tributes[1] = testState.discard[nextPlayer][1]; }
		if (tributes[0] == tributes[1]) { tributes[1] = -1; }
		if (showTests == 1) { printf("Tributes Revealed: <%i> <%i>\n", tributes[0], tributes[1]); }
		for (i = 0; i < 2; i++) {
			if (tributes[i] == copper || tributes[i] == silver || tributes[i] == gold) {
				testState.coins += 2;
			}
			else if (tributes[i] == estate || tributes[i] == duchy || tributes[i] == province || tributes[i] == gardens || tributes[i] == great_hall) {
				drawCard(currentPlayer, &testState);
				drawCard(currentPlayer, &testState);
			}
			else if (tributes[i] <= treasure_map && tributes[i] > 0) {
				testState.numActions += 2;
			}
		}
		int failed = checkTest(&testState, &runState, playerCards, showTests);
		if (showTests == 1) { printf("Number of tests failed: %i\n", failed); }
		totalFailed += failed;
	}
	printf("\nTotal number of tests failed: %i\n", totalFailed);
	return 0;
}
