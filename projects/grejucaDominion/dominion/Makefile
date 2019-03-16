CFLAGS= -Wall -fpic -coverage -lm -std=c99
EXE= playdom.exe playdom player player.exe unittest*[!.c] cardtest*[!.c] randomtestcard*[!.c]
TEST_DEPS = dominion.o rngs.o test_helpers.o
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

test_helpers.o: test_helpers.h test_helpers.c  
	gcc -c test_helpers.c -g $(CFLAGS)

randomtestcard1: randomtestcard1.c $(TEST_DEPS) 
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o test_helpers.o $(CFLAGS)

randomtestcard2: randomtestcard2.c $(TEST_DEPS) 
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o test_helpers.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c $(TEST_DEPS) 
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o test_helpers.o $(CFLAGS)

randomtestadventurerresults: randomtestadventurer.c
	make randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

randomtest2results: randomtestcard2.c
	make randomtestcard2
	./randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out

randomtest1results: randomtestcard1.c
	make randomtestcard1
	./randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out

unittest1: unittest1.c $(TEST_DEPS) 
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest2: unittest2.c $(TEST_DEPS) 
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest3: unittest3.c $(TEST_DEPS) 
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest4: unittest4.c $(TEST_DEPS) 
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o test_helpers.o $(CFLAGS)

cardtest1: cardtest1.c $(TEST_DEPS)
		gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o test_helpers.o $(CFLAGS)

cardtest2: cardtest2.c $(TEST_DEPS)
		gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o test_helpers.o $(CFLAGS)

cardtest3: cardtest3.c $(TEST_DEPS)
		gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o test_helpers.o $(CFLAGS)

cardtest4: cardtest4.c $(TEST_DEPS)
		gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittestresults: unittest* cardtest*
	echo "Dominion unit tests: " > tests.out 
	make unittest1 
	./unittest1 >> tests.out
	gcov -b dominion.c >> tests.out

	make unittest2 
	./unittest2 >> tests.out
	gcov -b dominion.c >> tests.out

	make unittest3 
	./unittest3 >> tests.out
	gcov -b dominion.c >> tests.out

	make unittest4 
	./unittest4 >> tests.out
	gcov -b dominion.c >> tests.out

	make cardtest1 
	./cardtest1 >> tests.out
	gcov -b dominion.c >> tests.out

	make cardtest2 
	./cardtest2 >> tests.out
	gcov -b dominion.c >> tests.out

	make cardtest3 
	./cardtest3 >> tests.out
	gcov -b dominion.c >> tests.out

	make cardtest4 
	./cardtest4 >> tests.out
	gcov -b dominion.c >> tests.out

	echo "number of tests: " >> tests.out
	grep -o "Test [0-9]" tests.out | wc -l >> tests.out

	echo "number of tests failed: " >> tests.out
	grep -o "FAIL" tests.out | wc -l >> tests.out

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
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
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o $(EXE) *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer
