CC=gcc
CFLAGS=-Wall -Werror -ansi -pedantic -g -O

mcafe: mcafe.o

test: mcafe
	./mcafe < test/mcafe.input > test/mcafe.output

.PHONY: test
