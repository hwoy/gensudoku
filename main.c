#include <stdio.h>
#include "sudoku.h"

int main(void)
{
	unsigned int i,j;
struct sgs_game game;
sgf_init(&game,NULL);	
sgs_setvalue(1,&game,0,0);
for(i=0;i<S_SQR;i++)
{
	if(!(i%S_ZSQR) && i) printf("\n");
	for(j=0;j<S_SQR;j++)
	{
		if(!(j%S_ZSQR) && j) printf("  ");
		printf("[%u,%u,%u,%u] ",game.board.unit[i][j].idx,game.board.unit[i][j].idy,game.board.unit[i][j].idz,sgs_getvalue_p(&game,j,i));
	}
	putchar('\n');
}
return 0;
}

