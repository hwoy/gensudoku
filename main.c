#include <stdio.h>
#include <time.h>
#include "sudoku.h"
#include "sudoku_io.h"
#include "function.h"
#include "opt.h"

/**************************************/
#define CH 0x20
#define SCH '*'

#define SBID time(NULL)
#define NBLANK 40
#define NBOARD 1
#define SD 5
#define NBSEED time(NULL)
#define FP stdout
/***************************************/
#define BSIZE 1024

static void genSudokus_rnd_solve(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch,unsigned int sd,unsigned int seed);

const char playername[]="Hwoy";
static const char *cptrarr_param[] =
  { "-sbid:","-nblank:" ,"-nboard:","-sd:" ,"-nbseed:","-solve","-h", NULL };
enum
{
  opt_sbid, opt_nblank, opt_nboard, opt_sd, opt_nbseed,opt_solve ,opt_h
};


int main(int argc,const char **argv)
{
  static char carray_buff[BSIZE], filename[BSIZE];
  int i,j;
  unsigned int ui_cindex,optflag;
  
  unsigned int sbid,nblank,nboard,sd,nbseed;
  FILE *fp;
  
struct sgs_game game;


/********** init default variables **********/
sbid=SBID;
nblank=NBLANK;
nboard=NBOARD;
sd=SD;
nbseed=NBSEED;
fp=FP;
/********** init default variables **********/
optflag=0;

  for (ui_cindex = DSTART; (i =opt_action (argc, argv, cptrarr_param, carray_buff,BSIZE, DSTART)) != e_optend; ui_cindex++)
  {
	 switch(i)
	 
	 {
		 case opt_sbid:
		 break;
		 
		 case opt_nblank:
		 break;
		 
		 case opt_nboard:
		 break;
		 
		 case opt_sd:
		 break;
		 
		 case opt_solve:
		 optflag|=POW2A(i);
		 break;
		 
		 case opt_h:
		 break;
		 
		 default:
		 break;
	 }
  }

sgf_init(&game,playername,sbid,nblank);

if(optflag&POW2A(opt_solve))
{
	genSudokus_rnd_solve(fp,&game,sbid,nboard,CH,sd,nbseed);
}
else
{
	genSudokus_rnd(fp,&game,sbid,nboard,CH,sd,nbseed);
}

fclose(fp);
return 0;
}

static void genSudokus_rnd_solve(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch,unsigned int sd,unsigned int seed)
{
	unsigned int i;
	for(i=0;i<num;i++)
	{
		genSudokus_rnd(fp,game,bid+i,1,ch,sd,seed);
		genBoards(fp,game,bid+i,1,ch);
	}
}
