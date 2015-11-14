#include <stdio.h>
#include <time.h>
#include "sudoku.h"
#include "sudoku_io.h"


#define CH '_'
#define SCH '*'

#define NBLANK 40


int main(void)
{
unsigned int i;
struct sgs_game game;

/*1447511034*/
sgf_init(&game,NULL,time(NULL),NBLANK);	
sgf_createsudoku(&game);

printBoard(stdout,&game,CH);
putchar('\n');


printValuep(stdout,&game,CH,SCH);
putchar('\n');

/*
printFindvalueUnique(stdout,&game,CH);
putchar('\n');

printFindvalueOne(stdout,&game,CH);
putchar('\n');
*/


return 0;
}
