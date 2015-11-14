#include <stdio.h>
#include "sudoku.h"
#include "sudoku_io.h"

void printValuep(FILE *fp,struct sgs_game *game,char ch)
{
unsigned int i,j,k;
fprintf(fp,"BOARD ID = %u\n\n",game->gameid);
for(i=0;i<S_SQR;i++)
{
	if(!(i%S_ZSQR) && i) fprintf(fp,"\n");
	for(j=0;j<S_SQR;j++)
	{
		if(!(j%S_ZSQR) && j) fprintf(fp,"\t");
		fprintf(fp,"[");
		for(k=0;k<S_SQR;k++)
		{
			if(sgf_getvalue(game,j,i)) fputc(ch,fp);
			else if(sgf_getvalue_p(game,j,i)&POW2A(k)) fprintf(fp,"%u",k+1);
			else fputc(sgf_getvalue_p(game,j,i)?ch:'*',fp);
		}
		fprintf(fp,"]");
	}
	fputc('\n',fp);
}
}

void printBoard(FILE *fp,struct sgs_game *game,char ch)
{
unsigned int i,j,k;
fprintf(fp,"BOARD ID = %u\n\n",game->gameid);
for(i=0;i<S_SQR;i++)
{
	if(!(i%S_ZSQR) && i) fprintf(fp,"\n");
	for(j=0;j<S_SQR;j++)
	{
		if(!(j%S_ZSQR) && j) fprintf(fp,"\t");
		fprintf(fp,"[");
			if((k=sgf_getvalue(game,j,i))) fprintf(fp,"%u",k);
			else fputc(ch,fp);
		fprintf(fp,"]");
	}
	fputc('\n',fp);
}
}
