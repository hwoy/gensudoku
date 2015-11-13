#include <stdio.h>
#include "sudoku.h"
#include "sudoku_io.h"

void showValuep(struct sgs_game *game,char ch)
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
			else putchar(ch);
		}
		printf("]");
	}
	putchar('\n');
}
}
