CC=gcc
bin=sudoku
CFLAGS=-O2 -std=c89 -pedantic #-Wall -Werror

.PHONY: all clean

all: $(bin)
$(bin): main.o sudoku.o sudoku_io.o
	$(CC) -o $(bin) main.o sudoku.o sudoku_io.o

clean:
	rm -f *.o *.exe $(bin)
	
main.o: main.c sudoku.h sudoku_io.h
sudoku.o: sudoku.c sudoku.h
sudoku_io.o: sudoku_io.c sudoku_io.h

