CC=gcc
CFLAGS=-g3 -std=c99 -Wall -pedantic

transpose: transpose.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o *.d