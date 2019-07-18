CFLAGS= -Wall -fpic -coverage -lm -std=c99

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

asserttrue.o: asserttrue.h asserttrue.c
	gcc -c asserttrue.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c dominion_helpers.h rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o asserttrue.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o asserttrue.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o asserttrue.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o asserttrue.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o asserttrue.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o asserttrue.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o asserttrue.o interface.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o asserttrue.o interface.o $(CFLAGS)

cardtest5: cardtest5.c dominion.o rngs.o asserttrue.o dominion_helpers.h
	gcc -o cardtest5 -g  cardtest5.c dominion.o rngs.o asserttrue.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o asserttrue.o dominion_helpers.h
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o asserttrue.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o asserttrue.o dominion_helpers.h
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o asserttrue.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o asserttrue.o dominion_helpers.h
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o asserttrue.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o asserttrue.o dominion_helpers.h
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o asserttrue.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o asserttrue.o dominion_helpers.h
	gcc -o unittest5 -g  unittest5.c dominion.o rngs.o asserttrue.o $(CFLAGS)

unittestresults:
	gcc -o unittest1 dominion.c rngs.c unittest1.c asserttrue.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c asserttrue.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o unittest3 dominion.c rngs.c unittest3.c asserttrue.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o unittest4 dominion.c rngs.c unittest4.c asserttrue.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o unittest5 dominion.c rngs.c unittest5.c asserttrue.c $(CFLAGS)
	unittest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c asserttrue.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c asserttrue.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c asserttrue.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c asserttrue.c interface.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	gcc -o cardtest5 dominion.c rngs.c cardtest5.c asserttrue.c $(CFLAGS)
	cardtest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

clean:
	rm -f *.o cardtest1 cardtest2 cardtest3