#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int initRandBaronState(struct gameState *state, int showTests) {
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
	//INITIALIZE RANDOM KINGDOM CARDS (MUST HAVE BARON)
	int kingdomCard[treasure_map + 1] = { 0 };
	kingdomCard[baron] = 1;
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
	int baronIndex;
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
		if (i == state->whoseTurn) { baronIndex = rand() % (state->handCount[state->whoseTurn]); }
		for (j = 0; j < state->handCount[i]; j++) {
			state->hand[i][j] = rand() % (treasure_map + 1);
			if (j == baronIndex) { state->hand[state->whoseTurn][j] = baron; }
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
	return baronIndex;
}

int checkTest(struct gameState *testState, struct gameState *runState, int showTests) {
	if (showTests == 1) { printf("-------------------------------------RUN CHECKS-------------------------------------\n"); }
	int i;
	int passed = 0;
	//CHECK SUPPLY COUNT
	if (showTests == 1) { printf("SUPPLY COUNTS <#: Expected value, Calculated value>:\n"); }
	for (i = 0; i <= treasure_map; i++) {
		if (showTests == 1) { printf("<%i: %i, %i>", i, testState->supplyCount[i], runState->supplyCount[i]); }
		passed += asserttrue(testState->supplyCount[i] == runState->supplyCount[i], showTests);
	}
	//CHECK COINS
	if (showTests == 1) { printf("Number of coins: <Expected: %i, Calculated: %i>\n", testState->coins, runState->coins); }
	passed += asserttrue(testState->coins == runState->coins, showTests);
	//CHECK NUMBER OF BUYS
	if (showTests == 1) { printf("Number of buys: <Expected: %i, Calculated: %i>\n", testState->numBuys, runState->numBuys); }
	passed += asserttrue(testState->numBuys == runState->numBuys, showTests);
	//CHECK HAND
	int testArray[treasure_map + 1] = { 0 };
	for (i = 0; i < testState->handCount[testState->whoseTurn]; i++) {
		testArray[testState->hand[testState->whoseTurn][i]]++;
	}
	int runArray[treasure_map + 1] = { 0 };
	for (i = 0; i < runState->handCount[runState->whoseTurn]; i++) {
		runArray[runState->hand[runState->whoseTurn][i]]++;
	}
	if (showTests == 1) { printf("Number of each card type in hand <#: Expected value, Calculated value>:\n"); }
	for (i = 0; i <= treasure_map; i++) {
		if (showTests == 1) { printf("<%i: %i, %i>", i, testArray[i], runArray[i]); }
		passed += asserttrue(testArray[i] == runArray[i], showTests);
		testArray[i] = 0;
		runArray[i] = 0;
	}
	//CHECK DECK
	for (i = 0; i < testState->deckCount[testState->whoseTurn]; i++) {
		testArray[testState->deck[testState->whoseTurn][i]]++;
	}
	for (i = 0; i < runState->deckCount[runState->whoseTurn]; i++) {
		runArray[runState->deck[runState->whoseTurn][i]]++;
	}
	if (showTests == 1) { printf("Number of each card type in deck <#: Expected value, Calculated value>:\n"); }
	for (i = 0; i <= treasure_map; i++) {
		if (showTests == 1) { printf("<%i: %i, %i>", i, testArray[i], runArray[i]); }
		passed += asserttrue(testArray[i] == runArray[i], showTests);
		testArray[i] = 0;
		runArray[i] = 0;
	}
	//CHECK DISCARD
	for (i = 0; i < testState->discardCount[testState->whoseTurn]; i++) {
		testArray[testState->discard[testState->whoseTurn][i]]++;
	}
	for (i = 0; i < runState->discardCount[runState->whoseTurn]; i++) {
		runArray[runState->discard[runState->whoseTurn][i]]++;
	}
	if (showTests == 1) { printf("Number of each card type in discard <#: Expected value, Calculated value>:\n"); }
	for (i = 0; i <= treasure_map; i++) {
		if (showTests == 1) { printf("<%i: %i, %i>", i, testArray[i], runArray[i]); }
		passed += asserttrue(testArray[i] == runArray[i], showTests);
	}
	return passed;
}

int main () {
	time_t t;
	srand((unsigned)time(&t));
	int i;
	int j;
	int showTests = 0;
	printf("\n******************************************************************************************\n");
	printf("                                 RANDOM TEST 1: Baron Card                                 \n");
	printf("******************************************************************************************\n");
	
	struct gameState testState;
	struct gameState runState;
	int baronIndex;
	int totalFailed = 0;
	for (j = 0; j < 100; j++) {
		if (showTests == 1) { printf("--------------------------------------TEST %i--------------------------------------\n", j + 1); }
		baronIndex = initRandBaronState(&runState, showTests);
		memcpy(&testState, &runState, sizeof(struct gameState));
		int currentPlayer = runState.whoseTurn;
		int choice = rand() % 2;
		if (showTests == 1) { printf("CHOICE %i\n", choice); }
		baronCase(&runState, choice);
		testState.numBuys++;
		//REMOVE BARON CARD
		for (i = baronIndex; i < testState.handCount[currentPlayer] - 1; i++) {
			testState.hand[currentPlayer][i] = testState.hand[currentPlayer][i + 1];
		}
		testState.handCount[currentPlayer]--;
		testState.discard[currentPlayer][testState.discardCount[currentPlayer]] = baron;
		testState.discardCount[currentPlayer]++;
		if (choice > 0) {
			//CHECKS IF THERE IS AN ESTATE
			int estateIndex = -1;
			for (i = 0; i < testState.handCount[currentPlayer]; i++) {
				if (testState.hand[currentPlayer][i] == estate) {
					estateIndex = i;
				}
			}
			//IF PLAYER HAS NO ESTATE
			if (estateIndex == -1) {
				if (testState.discardCount[currentPlayer] <= MAX_DECK && testState.supplyCount[estate] >= 0) {
					testState.discard[currentPlayer][testState.discardCount[currentPlayer]] = estate;
					testState.discardCount[currentPlayer]++;
					testState.supplyCount[estate]--;
				}
			}
			//IF PLAYER HAS ESTATE
			else {
				//COINS ARE INCREASED BY 4
				testState.coins += 4;
				//DISCARD HOLDS ESTATE
				testState.discard[currentPlayer][testState.discardCount[currentPlayer]] = estate;
				//DISCARD IS INCREASED
				testState.discardCount[currentPlayer]++;
				//REMOVE ESTATE FROM HAND
				for (i = estateIndex; i < testState.handCount[currentPlayer] - 1; i++) {
					testState.hand[currentPlayer][i] = testState.hand[currentPlayer][i + 1];
				}
				testState.handCount[currentPlayer]--;
			}
		}
		else {
			if (testState.discardCount[currentPlayer] <= MAX_DECK && testState.supplyCount[estate] >= 0) {
				testState.discard[currentPlayer][testState.discardCount[currentPlayer]] = estate;
				testState.discardCount[currentPlayer]++;
				testState.supplyCount[estate]--;
			}
		}
		int failed = checkTest(&testState, &runState, showTests);
		if (showTests == 1) { printf("Number of tests failed: %i\n", failed); }
		totalFailed += failed;
	}
	printf("Total number of tests failed: %i\n", totalFailed);
	return 0;
}
