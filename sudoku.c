#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

struct sgs_game *sgf_init(struct sgs_game *game,const char *playername)
{
	unsigned int x,y;
	
	for(y=0;y<S_SQR;y++)
	{
		for(x=0;x<S_SQR;x++)
		{
			game->board.unit[y][x].idy=y;
			game->board.unit[y][x].idx=x;
			game->board.unit[y][x].idz=(x%S_ZSQR)+(y%S_ZSQR)*S_ZSQR;
			game->board.unit[y][x].value=game->board.unit[y][x].valuep=0;
		}
	}
	
	game->playername=playername;
	srand(game->gameid=time(NULL));
	
	return game;
}
void sgs_setvalue(sgt_set value,struct sgs_game *game,unsigned int x,unsigned int y)
{
	game->board.unit[y][x].value|=POW2A(value-1);
}

sgt_set sgs_getvalue(struct sgs_game *game,unsigned int x,unsigned int y)
{
	return game->board.unit[y][x].value;
}

sgt_set sgs_getvalue_px(struct sgs_game *game,unsigned int y)
{
	unsigned int i;
	sgt_set set;
	for(set=0,i=0;i<S_SQR;i++)
	{
		set|=game->board.unit[y][i].value;
	}
	return (~set)&(POW2A(S_SQR)-1);
}

sgt_set sgs_getvalue_py(struct sgs_game *game,unsigned int x)
{
	unsigned int i;
	sgt_set set;
	for(set=0,i=0;i<S_SQR;i++)
	{
		set|=game->board.unit[i][x].value;
	}
	return (~set)&(POW2A(S_SQR)-1);
}

sgt_set sgs_getvalue_pz(struct sgs_game *game,unsigned int x,unsigned int y)
{
	unsigned int i,j;
	sgt_set set;
	set=0;
	for(i=(y/S_ZSQR)*S_ZSQR;i<S_ZSQR;i++)
	{
		for(j=(x/S_ZSQR)*S_ZSQR;j<S_ZSQR;j++)
		{
		set|=game->board.unit[i][j].value;
		}
	}
	return (~set)&(POW2A(S_SQR)-1);
}

sgt_set sgs_getvalue_p(struct sgs_game *game,unsigned int x,unsigned int y)
{
	return game->board.unit[y][x].valuep=sgs_getvalue_px(game,y)|sgs_getvalue_py(game,x)|sgs_getvalue_pz(game,x,y);
}

