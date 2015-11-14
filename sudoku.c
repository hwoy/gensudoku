#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

struct sgs_game *sgf_init(struct sgs_game *game,const char *playername,sgt_bid bid,unsigned int numstart)
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
	game->numstart=numstart;
	
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
	unsigned tmp[S_SQR],tmp2[S_SQR];
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
unsigned int i,j;

for(i=0;i<S_SQR;i++)
{
	for(j=0;j<S_SQR;j++)
	{

			if(sgf_getvalue_p(game,j,i)==0 && sgf_getvalue(game,j,i)==0 ) return 1;
	}
}
return 0;
}

void sgf_genboard(struct sgs_game *game)
{
	unsigned int tmp[S_SQR];
	unsigned int x,y,z,i,j,k,m,n;
	unsigned int X,Y;
	
	
	srand(game->bid);
	
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
				if(!m) sgf_setvalue(0,game,x,y);


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

				sgf_setvalue(tmp[sgf_random(0,m-1)],game,x,y);
				
			}
		}
				
				
}
