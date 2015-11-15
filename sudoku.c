#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

struct sgs_game *sgf_init(struct sgs_game *game,const char *playername,sgt_bid bid,unsigned int numblank)
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
	game->bid=bid;
	game->numblank=numblank;
	
	return game;
}
void sgf_setvalue(sgt_set value,struct sgs_game *game,unsigned int x,unsigned int y)
{
	game->board.unit[y][x].value=value;
}

sgt_set sgf_getvalue(struct sgs_game *game,unsigned int x,unsigned int y)
{
	return game->board.unit[y][x].value;
}

sgt_set sgf_getvalue_x(struct sgs_game *game,unsigned int y)
{
	unsigned int i;
	sgt_set set;
	for(set=0,i=0;i<S_SQR;i++)
	{
		set|=(game->board.unit[y][i].value>0)?POW2A(game->board.unit[y][i].value-1):0;
	}
	return (set)&(POW2A(S_SQR)-1);
}

sgt_set sgf_getvalue_y(struct sgs_game *game,unsigned int x)
{
	unsigned int i;
	sgt_set set;
	for(set=0,i=0;i<S_SQR;i++)
	{
		set|=(game->board.unit[i][x].value>0)?POW2A(game->board.unit[i][x].value-1):0;
	}
	return (set)&(POW2A(S_SQR)-1);
}

sgt_set sgf_getvalue_z(struct sgs_game *game,unsigned int x,unsigned int y)
{
	unsigned int i,j,m,n;
	sgt_set set;
	set=0;
	for(m=i=(y/S_ZSQR)*S_ZSQR;i<m+S_ZSQR;i++)
	{
		for(n=j=(x/S_ZSQR)*S_ZSQR;j<n+S_ZSQR;j++)
		{
		set|=(game->board.unit[i][j].value>0)?POW2A(game->board.unit[i][j].value-1):0;
		}
	}
	return (set)&(POW2A(S_SQR)-1);
}

sgt_set sgf_getvalue_p(struct sgs_game *game,unsigned int x,unsigned int y)
{
	return (~(game->board.unit[y][x].valuep=sgf_getvalue_x(game,y)|sgf_getvalue_y(game,x)|sgf_getvalue_z(game,x,y)))&(POW2A(S_SQR)-1);
}

unsigned int sgf_countvalue_set(sgt_set value)
{
	unsigned int i,j;
	for(i=0,j=0;i<S_SQR;i++)
	{
		if(value&POW2A(i)) j++;
	}
	return j;
}
unsigned int sgf_countvalue(struct sgs_game *game,unsigned int x,unsigned int y)
{

	return sgf_countvalue_set(game->board.unit[y][x].value);

}

void sgf_srandom (int seed)
{
  srand (seed);
}

int sgf_random (int min, int max)
{
  return min <= max ? min + (rand () % (max - min + 1)) : -1;
}

unsigned int sgf_log2a (unsigned int num)
{
	unsigned int i;
	for(i=0; (num>>i) > 1;i++);
	return i;
}



unsigned int sgf_findvalueone(struct sgs_game *game,unsigned int x,unsigned int y)
{
unsigned int i;
if((sgf_countvalue_set(i=sgf_getvalue_p(game,x,y))==1) && !sgf_getvalue(game,x,y)) return sgf_log2a(i)+1;

	return 0;
}

unsigned int sgf_findvalueunique(struct sgs_game *game,unsigned int x,unsigned int y)
{
	unsigned int i,j,m,n;
	sgt_set set;
	
	set=0;
	for(i=0;i<S_SQR;i++)
	{
		if(i!=x) set|=sgf_getvalue_p(game,i,y);
	}
	
	for(i=0;i<S_SQR;i++)
	{
		if(i!=y) set|=sgf_getvalue_p(game,x,i);
	}
	
	for(m=i=(y/S_ZSQR)*S_ZSQR;i<m+S_ZSQR;i++)
	{
		for(n=j=(x/S_ZSQR)*S_ZSQR;j<n+S_ZSQR;j++)
		{
		if(j!=x || i!=y) set|=sgf_getvalue_p(game,j,i);
		}
	}
	
	m=sgf_getvalue_p(game,x,y);
	for(i=0;i<S_SQR;i++)
	{
		if((m&POW2A(i)) && !(set&POW2A(i)) && !sgf_getvalue(game,x,y)) return i+1;
	}
		
		return 0;
}


unsigned int sgf_getobstruct(struct sgs_game *game)
{
unsigned int i,j,k;

for(k=0,i=0;i<S_SQR;i++)
{
	for(j=0;j<S_SQR;j++)
	{

			if(sgf_getvalue_p(game,j,i)==0 && sgf_getvalue(game,j,i)==0 ) k++;
	}
}
return k;
}

int sgf_genboard(struct sgs_game *game)
{
	unsigned int tmp[S_SQR];
	unsigned int x,y,z,i,j,k,m;
	unsigned int X,Y;
	
	sgf_resetboard(game);
	
	for(z=0;z<=S_ZSQR*2;z+=3)
	{
		for(y=z;y<S_ZSQR+z;y++)
		{
		for(x=z;x<S_ZSQR+z;x++)
			{
			if((x%S_ZSQR)>=(S_ZSQR) || (y%S_ZSQR)>=(S_ZSQR)) continue;
			
			if(sgf_getvalue(game,x,y)!=0) continue;
			i=sgf_getvalue_p(game,x,y);
			if(!i) continue;
			
			for(m=0,j=0;j<S_SQR;j++)
				{
				if(i&POW2A(j)) tmp[m++]=j+1;
				}

				sgf_setvalue(tmp[sgf_random(0,m-1)],game,x,y);
			
			}
		}	
	}	
	

		for(y=0;y<S_SQR;y++)
		{
		for(x=0;x<S_SQR;x++)
			{
			
			if(x%S_ZSQR != y%S_ZSQR ) continue;
			
				if(sgf_getvalue(game,x,y)!=0) continue;
				i=sgf_getvalue_p(game,x,y);
				if(!i) continue;
				for(m=0,j=0;j<S_SQR;j++)
				{
				if(i&POW2A(j)) tmp[m++]=j+1;
				}
				
				do{
				sgf_setvalue((k=tmp[sgf_random(0,m-1)]),game,x,y);
				for(;k<m-1;k++)
				{
					tmp[k]=tmp[k+1];
				}
				}while(sgf_getobstruct(game) && ((m--)>1));


loop1:	
		for(Y=0;Y<S_SQR;Y++)
		{
		for(X=0;X<S_SQR;X++)
			{
				if((i=sgf_findvalueone(game,X,Y))) 
				{
					sgf_setvalue(i,game,X,Y);
					goto loop1;
				}
			}
		}
		for(Y=0;Y<S_SQR;Y++)
		{
		for(X=0;X<S_SQR;X++)
			{
				if((i=sgf_findvalueunique(game,X,Y))) 
				{
					sgf_setvalue(i,game,X,Y);
					goto loop1;
				}
			}
		}		
		
		
		
			}
		}
		
		for(y=0;y<S_SQR;y++)
		{
		for(x=0;x<S_SQR;x++)
			{
			if(sgf_getvalue(game,x,y)!=0) continue;
			i=sgf_getvalue_p(game,x,y);
			if(!i) continue;
			
			for(m=0,j=0;j<S_SQR;j++)
				{
				if(i&POW2A(j)) tmp[m++]=j+1;
				}

				do{
				sgf_setvalue((k=tmp[sgf_random(0,m-1)]),game,x,y);
				for(;k<m-1;k++)
				{
					tmp[k]=tmp[k+1];
				}
				}while(sgf_getobstruct(game) && ((m--)>1));
				
			}
		}
				
	return sgf_completeboard(game);			
}

int sgf_completeboard(struct sgs_game *game)
{
	unsigned int x,y,j;
	
		for(j=0,y=0;y<S_SQR;y++)
		{
		for(x=0;x<S_SQR;x++)
			{
				if(!sgf_getvalue(game,x,y)) j++;
			}
		}
		
		return j;
	
}

void sgf_resetboard(struct sgs_game *game)
{
	unsigned int x,y;
	
		for(y=0;y<S_SQR;y++)
		{
		for(x=0;x<S_SQR;x++)
			{
				sgf_setvalue(0,game,x,y);
			}
		}
		
	
}

sgt_bid sgf_findboard(struct sgs_game *game)
{
	sgf_srandom(game->bid);
	while(sgf_genboard(game));
	
	return sgf_getbid(game);
}

void sgf_setbid(struct sgs_game *game,sgt_bid bid)
{
	game->bid=bid;
}

sgt_bid sgf_getbid(struct sgs_game *game)
{
	return game->bid;
}

void sgf_createsudoku(struct sgs_game *game)
{
	unsigned int tmp[S_SQR*S_SQR];
	unsigned int x,y,i,j,k,m;
		for(y=0;y<S_SQR;y++)
		{
		for(x=0;x<S_SQR;x++)
			{
				tmp[x+y*S_SQR]=x+y*S_SQR;
			}
		}			
	
	sgf_findboard(game);
		for(y=0;y<S_SQR;y++)
		{
		for(x=0;x<S_SQR;x++)
			{
				game->sboard.unit[y][x].value=game->board.unit[y][x].value;
			}
		}
	
	for(j=S_SQR*S_SQR,i=0;i<game->numblank;i++)
	{
		k=tmp[m=sgf_random(0,--j)];
		sgf_setvalue(0,game,k%S_SQR,k/S_SQR);
		for(;m<j;m++)
		{
			tmp[m]=tmp[m+1];
		}
	}
}

void sgf_createsudoku_rnd(struct sgs_game *game,unsigned int sd)
{
	sgf_setnblank(game,sgf_random(sgf_getnblank(game)-sd,sgf_getnblank(game)+sd));
	sgf_createsudoku(game);
}

void sgf_setnblank(struct sgs_game *game,unsigned int numblank)
{
	game->numblank=numblank;
}
unsigned int sgf_getnblank(struct sgs_game *game)
{
	return game->numblank;
}

