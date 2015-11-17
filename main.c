#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"
#include "sudoku_io.h"
#include "function.h"
#include "opt.h"

/****************** Constances ********************/
#define CH 0x20
#define SCH '*'

#define NBLANK 40
#define NBOARD 1
#define SD 5
#define FP stdout

#define MAX_NBLANK (S_SQR*S_SQR)

#define BSIZE 1024

#ifdef _DEVRAND_
#define SBID devrandom(devname)
#define NBSEED devrandom(devname)
#else
	
#define SBID time(NULL)
#define NBSEED time(NULL)	

#endif
/****************** Constances ********************/

static void genSudokus_rnd_solve(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch,unsigned int sd,unsigned int seed);
static int showErr (const char **str, int errno, const char *msg);
static void showHelp (const char *str, const char **param,const char **hparam);
static unsigned int basename (const char *ch);
static unsigned int devrandom(const char *devname);

static const char dname[]="/dev/urandom";
static const char *devname;

static const char playername[]="Hwoy";
static const char *cptrarr_param[] =
  { "-sbid:","-nblank:" ,"-nboard:", "-sd:" ,"-nbseed:","-solve",  "-file:","-devrandom","-devpath:","-timerandom","-h", NULL };
enum
{
  opt_sbid,  opt_nblank, opt_nboard, opt_sd, opt_nbseed,opt_solve ,opt_file,opt_dev,      opt_devpath,  opt_time,    opt_h
};
static const char *helpparam[] =
  { "start bid", "numbers of blank", "numbers of board", "SD", "nblank seed", "Solve games","Out put file", "dev random", "dev random with path","time random","Help",
  NULL
};
static const char *err_str[] =
  { "Invalid option", "Not an unsigned integer","NBLANK is over a limit","NBLANK and SD are not balance","Can not assigned a file", NULL
};
enum
{
  err_inv, err_ni,err_nb,err_nsd,err_file
};

int main(int argc,const char **argv)
{
  static char carray_buff[BSIZE], filename[BSIZE],devfilename[BSIZE];
  int i,j;
  unsigned int ui_cindex;
  
  unsigned int sbid,nblank,nboard,sd,nbseed;
  FILE *fp;
  
  void (*genSudokusptr)(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch,unsigned int sd,unsigned int seed);
  
struct sgs_game game;


/********** init default variables **********/
sbid=SBID;
nblank=NBLANK;
nboard=NBOARD;
sd=SD;
nbseed=NBSEED;
fp=FP;
devname=dname;
genSudokusptr=genSudokus_rnd;
/********** init default variables **********/

filename[0]=0;

  for (ui_cindex = DSTART; (i =opt_action (argc, argv, cptrarr_param, carray_buff,BSIZE, DSTART)) != e_optend; ui_cindex++)
  {

	 switch(i)
	 
	 {
		 case opt_sbid:
			if (!isUint (carray_buff))
			return showErr (err_str, err_ni, carray_buff);
			sbid=s2ui (carray_buff);
		 break;
		 
		 case opt_nblank:
			if (!isUint (carray_buff))
			return showErr (err_str, err_ni, carray_buff);
			nblank=s2ui (carray_buff);
			
			if(nblank>MAX_NBLANK)
			{
				j=showErr (err_str, err_nb, carray_buff);
				fprintf(stderr,"NBLANK LIMIT is %u\n",MAX_NBLANK);
				return j;
			}
			
			if((sd>nblank) || ((nblank+sd)>MAX_NBLANK))
			{
				j=showErr (err_str, err_nsd, carray_buff);
				fprintf(stderr,"NBLANK > SD ans NBLANK+SD <= %u\n",MAX_NBLANK);
				return j;
			}

		 break;
		 
		 case opt_nboard:
			if (!isUint (carray_buff))
			return showErr (err_str, err_ni, carray_buff);
			nboard=s2ui (carray_buff);
		 break;
		 
		 case opt_sd:
			if (!isUint (carray_buff))
			return showErr (err_str, err_ni, carray_buff);
			sd=s2ui (carray_buff);
			
			if((sd>nblank) || ((nblank+sd)>MAX_NBLANK))
			{
				j=showErr (err_str, err_nsd, carray_buff);
				fprintf(stderr,"NBLANK >= SD and NBLANK+SD <= %u\n",MAX_NBLANK);
				return j;
			}
		 break;
		 
		 case opt_nbseed:
			if (!isUint (carray_buff))
			return showErr (err_str, err_ni, carray_buff);
			nbseed=s2ui (carray_buff);
		 break;		 
		 
		 case opt_solve:
		 genSudokusptr=genSudokus_rnd_solve;
		 break;
		 
		 case opt_file:
		 strcpy(filename,carray_buff);
		 break;
		 
		 
		 case opt_devpath:
		 strcpy(devfilename,carray_buff);
		 devname=devfilename;
		 
		 case opt_dev:
		 sbid=devrandom(devname);
		 nbseed=devrandom(devname);
		 break;
		 
		 case opt_time:
		 sbid=time(NULL);
		 nbseed=time(NULL);
		 break;
		 
		 case opt_h:
			showHelp (argv[0], cptrarr_param, helpparam);
			return 1;
		 
		 default:
	  showHelp (argv[0], cptrarr_param, helpparam);
	  return showErr (err_str, err_inv, carray_buff);
	 }
  }

  if(filename[0])
  {
	  if(!(fp=fopen(filename,"w")))
	  {
		 return showErr (err_str, err_file, carray_buff); 
	  }
  }
  
sgf_init(&game,playername,sbid,nblank);

genSudokusptr(fp,&game,sbid,nboard,CH,sd,nbseed);


fclose(fp);
return 0;
}

static void genSudokus_rnd_solve(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch,unsigned int sd,unsigned int seed)
{
	unsigned int i;
	for(i=0;i<num;i++)
	{
		genSudokus_rnd(fp,game,bid+i,1,ch,sd,seed+i);
		sgf_srandom(bid+i);
		genBoards(fp,game,bid+i,1,ch);
	}
}

static int showErr (const char **str, int errno, const char *msg)
{
  fprintf (stderr, "ERR %d: %s : %s\n", errno, msg, str[errno]);
  return -1 * (errno + 1);
}

static unsigned int basename (const char *ch)
{
  unsigned int i, j;
  for (i = 0, j = 0; ch[i]; i++)
    {
      if (ch[i] == '\\' || ch[i] == '/')
	{
	  j = i;
	}
    }
  return (j == 0) ? 0 : j + 1;
}

static void showHelp (const char *str, const char **param, const char **hparam)
{
  unsigned int i;
  
  fprintf (stderr,"\n%s [ENGINE VERSION = %u.%u.%u]\n",&str[basename (str)],SUDOKU_ENGINE_MAJOR_VERSION,SUDOKU_ENGINE_MINOR_VERSION,SUDOKU_ENGINE_SMINOR_VERSION);
  fprintf (stderr, "USAGE: %s [option list]\n\n", &str[basename (str)]);

  fprintf (stderr, "[OPTIONS]\n");

  for (i = 0; param[i] && hparam[i]; i++)
    {
      fprintf (stderr, "%10s\t\t%s\n", param[i], hparam[i]);
    }
  fprintf (stderr, "\n");

  fprintf (stderr, "[DEFAULT]\n");
  #ifdef _DEVRAND_
	fprintf (stderr, "%10s=%s\n", param[0], "dev random");
  #else
	fprintf (stderr, "%10s=%s\n", param[0], "time random");
  #endif
  fprintf (stderr, "%10s=%u\n", param[1], NBLANK);
  fprintf (stderr, "%10s=%u\n", param[2], NBOARD);
  fprintf (stderr, "%10s=%u\n", param[3], SD);
  #ifdef _DEVRAND_
	fprintf (stderr, "%10s=%s\n", param[4], "dev random");
  #else
	fprintf (stderr, "%10s=%s\n", param[4], "time random");
  #endif
  fprintf (stderr, "%10s=%s\n", param[6], "stdout");
  fprintf (stderr, "%10s=%s\n", param[8], dname);
  fprintf (stderr, "\n");
}


static unsigned int devrandom(const char *devname)
{
	unsigned int i,j,k;
	FILE *fp;
	
	if(!(fp=fopen(devname,"rb"))) return 0;
	
	for(k=0,i=0;i<sizeof(j);i+=sizeof(char),k++)
		((char *)(&j))[k]=fgetc(fp);
	
	fclose(fp);
	return j;
}
