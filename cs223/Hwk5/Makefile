CC=gcc
CFLAGS=-g3 -std=c99 -Wall -pedantic

ants: ants.c hash.o
	$(CC) $(CFLAGS) -o $@ $^

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *.d