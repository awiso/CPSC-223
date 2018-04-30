CC=gcc
CFLAGS=-g3 -std=c99 -Wall -pedantic

testDeck: deck.o testDeck.o
	$(CC) $(CFLAGS) -o $@ $^
testDeck.o: /c/cs223/Hwk4/testDeck.c
	$(CC) $(CFLAGS) -c $^
deck.o: deck.c
	$(CC) $(CFLAGS) -c $^
clean:
	$(RM) *.o *.d