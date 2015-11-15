#include <stdio.h>
#include <time.h>
#include "sudoku.h"
#include "sudoku_io.h"

void printValuep(FILE *fp,struct sgs_game *game,char ch,char sch)
{
unsigned int i,j,k;
fprintf(fp,"BOARD_ID = %u\n",game->bid);
fprintf(fp,"N_BLANK = %u\n\n",game->numblank);

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
			else fputc(sgf_getvalue_p(game,j,i)?ch:sch,fp);
		}
		fprintf(fp,"]");
	}
	fputc('\n',fp);
}
}

void printFindvalueUnique(FILE *fp,struct sgs_game *game,char ch)
{
unsigned int i,j,k;
fprintf(fp,"BOARD_ID = %u\n",game->bid);
fprintf(fp,"N_BLANK = %u\n\n",game->numblank);

for(i=0;i<S_SQR;i++)
{
	if(!(i%S_ZSQR) && i) fprintf(fp,"\n");
	for(j=0;j<S_SQR;j++)
	{
		if(!(j%S_ZSQR) && j) fprintf(fp,"\t");
		fprintf(fp,"[");
		
			if((k=sgf_findvalueunique(game,j,i))) fprintf(fp,"%u",k);
			else fputc(ch,fp);

		fprintf(fp,"]");
	}
	fputc('\n',fp);
}
}

void printFindvalueOne(FILE *fp,struct sgs_game *game,char ch)
{
unsigned int i,j,k;
fprintf(fp,"BOARD_ID = %u\n",game->bid);
fprintf(fp,"N_BLANK = %u\n\n",game->numblank);

for(i=0;i<S_SQR;i++)
{
	if(!(i%S_ZSQR) && i) fprintf(fp,"\n");
	for(j=0;j<S_SQR;j++)
	{
		if(!(j%S_ZSQR) && j) fprintf(fp,"\t");
		fprintf(fp,"[");
		
			if((k=sgf_findvalueone(game,j,i))) fprintf(fp,"%u",k);
			else fputc(ch,fp);

		fprintf(fp,"]");
	}
	fputc('\n',fp);
}
}

void printBoard(FILE *fp,struct sgs_game *game,char ch)
{
unsigned int i,j,k;
fprintf(fp,"BOARD_ID = %u\n",game->bid);
fprintf(fp,"N_BLANK = %u\n\n",game->numblank);

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

void genBoards(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch)
{
	unsigned int i;
	for(i=0;i<num;i++)
{
sgf_setbid(game,i+bid);
sgf_findboard(game);


printBoard(stdout,game,ch);
putchar('\n');
}

}

void genSudokus(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch)
{
	unsigned int i;
	for(i=0;i<num;i++)
{
sgf_setbid(game,i+bid);
sgf_createsudoku(game);

printBoard(stdout,game,ch);
putchar('\n');
}

}

void genSudokus_rnd(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch,unsigned int sd)
{
	unsigned int i,j;
	sgf_srandom(time(NULL));
	for(i=0;i<num;i++)
{
sgf_setbid(game,i+bid);
j=sgf_getnblank(game);
sgf_createsudoku_rnd(game,sd);
printBoard(stdout,game,ch);
sgf_setnblank(game,j);
putchar('\n');
}

}
