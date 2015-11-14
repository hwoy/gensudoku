#include <stdio.h>
#include <time.h>
#include "sudoku.h"
#include "sudoku_io.h"


#define CH '-'


int main(void)
{
/*unsigned int x,y;*/
struct sgs_game game;
sgf_init(&game,NULL,time(NULL),15);	
/*
sgf_setvalue(1,&game,0,0);sgf_setvalue(2,&game,1,0);sgf_setvalue(3,&game,2,0);
sgf_setvalue(4,&game,0,1);sgf_setvalue(5,&game,1,1);sgf_setvalue(6,&game,2,1);
sgf_setvalue(7,&game,0,2);sgf_setvalue(8,&game,1,2);sgf_setvalue(9,&game,2,2);

printValuep(stdout,&game,CH);
putchar('\n');
*/
sgf_genboard(&game);
printBoard(stdout,&game,CH);

printValuep(stdout,&game,CH);
putchar('\n');

return 0;
}
