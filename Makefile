bin=gensudoku
CFLAGS=-O2 -std=c89 -pedantic -Wall -Werror # -D_DEVRAND_ #for better random in unix enviroment

.PHONY: all clean

all: $(bin)
$(bin): main.o sudoku.o sudoku_io.o opt.o function.o
	$(CC) -o $(bin) main.o sudoku.o sudoku_io.o opt.o function.o

clean:
	rm -f *.o *.exe $(bin)
	
function.o: function.c function.h
main.o: main.c sudoku.h sudoku_io.h function.h opt.h
opt.o: opt.c opt.h
sudoku.o: sudoku.c sudoku.h
sudoku_io.o: sudoku_io.c sudoku.h sudoku_io.h

