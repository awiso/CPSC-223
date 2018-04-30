CC=gcc
CFLAGS=-g3 -std=c99 -Wall -pedantic

encode: encode.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o *.d