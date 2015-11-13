CC=gcc
bin=sudoku
CFLAGS=-O2 -std=c89 -pedantic -Wall -Werror

.PHONY: all clean

all: main.o sudoku.o
	$(CC) -o $(bin) main.o sudoku.o
main.o: main.c sudoku.h
sudoku.o: sudoku.c sudoku.h

clean:
	rm -f *.o *.exe $(bin)

