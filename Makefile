CC=gcc
CFLAGS=-Wall -Werror -ansi -pedantic -g -O -D'sleep(x)='
LDLIBS=-lrt

mcafe: mcafe.o fsm.o

test: mcafe
	grep -v '^#' test/mcafe.input | ./mcafe > test/mcafe.output

clean:
	rm -f *.o mcafe

.PHONY: test

