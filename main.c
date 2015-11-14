#include <stdio.h>
#include <time.h>
#include "sudoku.h"
#include "sudoku_io.h"


#define CH '_'
#define SCH '*'


int main(void)
{
unsigned int i;
struct sgs_game game;


sgf_init(&game,NULL,time(NULL),15);	
sgf_genboard(&game);

printBoard(stdout,&game,CH);
putchar('\n');

printValuep(stdout,&game,CH,SCH);
putchar('\n');

printFindvalueUnique(stdout,&game,CH);
putchar('\n');

printFindvalueOne(stdout,&game,CH);
putchar('\n');

if(sgf_getobstruct(&game)) printf("***OBSTRUCTION***\n");
putchar('\n');


return 0;
}
