CC=gcc
CFLAGS=-g3 -std=c99 -Wall -pedantic

testNum: num.o testNum.o
	$(CC) $(CFLAGS) -o $@ $^
testNum.o: /c/cs223/Hwk3/testNum.c
	$(CC) $(CFLAGS) -c $^
num.o: num.c
	$(CC) $(CFLAGS) -c $^
clean:
	$(RM) *.o *.d

