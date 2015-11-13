#include "sudoku.h"

struct sgs_game *sgf_init(struct sgs_game *game,const char *playername,sgt_gameid gameid,unsigned int numstart)
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
	game->gameid=gameid;
	game->numstart=numstart;
	
	return game;
}
void sgs_setvalue(sgt_set value,struct sgs_game *game,unsigned int x,unsigned int y)
{
	game->board.unit[y][x].value=value;
}

sgt_set sgs_getvalue(struct sgs_game *game,unsigned int x,unsigned int y)
{
	return game->board.unit[y][x].value;
}

sgt_set sgs_getvalue_x(struct sgs_game *game,unsigned int y)
{
	unsigned int i;
	sgt_set set;
	for(set=0,i=0;i<S_SQR;i++)
	{
		set|=(game->board.unit[y][i].value>0)?POW2A(game->board.unit[y][i].value-1):0;
	}
	return (set)&(POW2A(S_SQR)-1);
}

sgt_set sgs_getvalue_y(struct sgs_game *game,unsigned int x)
{
	unsigned int i;
	sgt_set set;
	for(set=0,i=0;i<S_SQR;i++)
	{
		set|=(game->board.unit[i][x].value>0)?POW2A(game->board.unit[i][x].value-1):0;
	}
	return (set)&(POW2A(S_SQR)-1);
}

sgt_set sgs_getvalue_z(struct sgs_game *game,unsigned int x,unsigned int y)
{
	unsigned int i,j;
	sgt_set set;
	set=0;
	for(i=(y/S_ZSQR)*S_ZSQR;i<S_ZSQR;i++)
	{
		for(j=(x/S_ZSQR)*S_ZSQR;j<S_ZSQR;j++)
		{
		set|=(game->board.unit[i][j].value>0)?POW2A(game->board.unit[i][j].value-1):0;
		}
	}
	return (set)&(POW2A(S_SQR)-1);
}

sgt_set sgs_getvalue_p(struct sgs_game *game,unsigned int x,unsigned int y)
{
	return ~(game->board.unit[y][x].valuep=sgs_getvalue_x(game,y)|sgs_getvalue_y(game,x)|sgs_getvalue_z(game,x,y))&(POW2A(S_SQR)-1);
}

unsigned int sgs_countvalue(struct sgs_game *game,unsigned int x,unsigned int y)
{
	unsigned int i,j;
	for(i=0,j=0;i<S_SQR;i++)
	{
		if(game->board.unit[y][x].value&POW2A(i)) j++;
	}
	return j;
}

