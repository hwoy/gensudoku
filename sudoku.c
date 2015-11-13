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
	game->board.unit[y][x].value=value;
}

sgt_set sgs_getvalue(struct sgs_game *game,unsigned int x,unsigned int y)
{
	return game->board.unit[y][x].value;
}