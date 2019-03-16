CFLAGS= -Wall -fpic -coverage -lm -std=c99

TESTLOG=unittestresults.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

runrandomtests: randomtestcard2 randomtestcard2 randomtestadventurer
	./randomtestcard1 > randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

unittestresults: unittest1 unittest2 unittest3 unittest4 card1test card2test card3test card4test
	echo "Result for running unit tests:" > $(TESTLOG)

	echo "unittest1.c:" >> $(TESTLOG)
	./unittest1 >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

	echo "unittest2.c:" >> $(TESTLOG)
	./unittest2 >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

	echo "unittest3.c:" >> $(TESTLOG)
	./unittest3 >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

	echo "unittest4.c:" >> $(TESTLOG)
	./unittest4 >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

	echo "card1test.c:" >> $(TESTLOG)
	./card1test >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

	echo "card2test.c:" >> $(TESTLOG)
	./card2test >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

	echo "card3test.c:" >> $(TESTLOG)
	./card3test >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

	echo "card4test.c:" >> $(TESTLOG)
	./card4test >> $(TESTLOG)
	gcov -b dominion.c >> $(TESTLOG)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

card1test: card1test.c dominion.o rngs.o
	gcc -o card1test -g card1test.c dominion.o rngs.o $(CFLAGS)

card2test: card2test.c dominion.o rngs.o
	gcc -o card2test -g card2test.c dominion.o rngs.o $(CFLAGS)

card3test: card3test.c dominion.o rngs.o
	gcc -o card3test -g card3test.c dominion.o rngs.o $(CFLAGS)

card4test: card4test.c dominion.o rngs.o
	gcc -o card4test -g card4test.c dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov -b >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
