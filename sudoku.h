#define S_SQR 9
#define S_ZSQR 3

typedef unsigned short sgt_set;
typedef unsigned int sgt_gameid;
struct sgs_unit
{
	unsigned int idx;
	unsigned int idy;
	unsigned int idz;
	
	sgt_set setx;
	sgt_set sety;
	sgt_set setz;
	
	sgt_set setp;
};

struct sgs_board
{
	struct sgs_unit unit[S_SQR][S_SQR];
};

struct sgs_game
{
	sgt_gameid gameid;
	struct sgs_board board;
	const char *playername;
};

struct sgs_game *sgf_init(struct sgs_game *game,const char *playername);