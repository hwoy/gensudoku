#include <stdio.h>
#include "sudoku.h"

void showValuep(struct sgs_game *game);

int main(void)
{
	/*unsigned int i,j;*/
struct sgs_game game;
sgf_init(&game,NULL);	

sgs_setvalue(1,&game,0,0);sgs_setvalue(2,&game,1,0);sgs_setvalue(3,&game,2,0);
sgs_setvalue(4,&game,0,1);sgs_setvalue(5,&game,1,1);sgs_setvalue(6,&game,2,1);
sgs_setvalue(7,&game,0,2);sgs_setvalue(8,&game,1,2);sgs_setvalue(9,&game,2,2);

showValuep(&game);

/*
for(i=0;i<S_SQR;i++)
{
	if(!(i%S_ZSQR) && i) printf("\n");
	for(j=0;j<S_SQR;j++)
	{
		if(!(j%S_ZSQR) && j) printf("\t");
		printf(" [%u,%u,%u,%3u]",game.board.unit[i][j].idx,game.board.unit[i][j].idy,game.board.unit[i][j].idz,sgs_getvalue_p(&game,j,i));
	}
	putchar('\n');
}
*/
return 0;
}

void showValuep(struct sgs_game *game)
{
unsigned int i,j,k;
for(i=0;i<S_SQR;i++)
{
	if(!(i%S_ZSQR) && i) printf("\n");
	for(j=0;j<S_SQR;j++)
	{
		if(!(j%S_ZSQR) && j) printf("\t");
		printf("[");
		for(k=0;k<S_SQR;k++)
		{
			if(sgs_getvalue_p(game,j,i)&POW2A(k)) printf("%u",k+1);
			else printf("-");
		}
		printf("]");
	}
	putchar('\n');
}
}