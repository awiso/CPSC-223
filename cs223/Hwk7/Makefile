CC=gcc
CFLAGS=-g3 -std=c99 -Wall -pedantic

testArray: testArray.c array.o array.h
	$(CC) $(CFLAGS) -o $@ $^
array.o: array.c array.h
	$(CC) $(CFLAGS) -c $^
clean:
	$(RM) *.o *.d
