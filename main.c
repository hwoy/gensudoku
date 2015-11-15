#include <stdio.h>
#include <time.h>
#include "sudoku.h"
#include "sudoku_io.h"


#define CH '_'
#define SCH '*'

#define NBLANK 40


int main(void)
{
struct sgs_game game;

sgf_init(&game,NULL,time(NULL),NBLANK);

/*	
sgf_createsudoku(&game);
*/

/*
printValuep(stdout,&game,CH,SCH);
putchar('\n');
*/
/*
printFindvalueUnique(stdout,&game,CH);
putchar('\n');

printFindvalueOne(stdout,&game,CH);
putchar('\n');
*/

genSudokus(stdout,&game,0,10,CH);

return 0;
}
