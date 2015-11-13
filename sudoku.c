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
			game->board.unit[y][x].setx=game->board.unit[y][x].sety=game->board.unit[y][x].setz=game->board.unit[y][x].setp=0;
		}
	}
	
	game->playername=playername;
	srand(game->gameid=time(NULL));
	
	return game;
}
