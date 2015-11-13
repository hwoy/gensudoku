#define S_SQR 9
#define S_ZSQR 3

#define POW2A(x) (1<<(x))

typedef unsigned short sgt_set;
typedef unsigned int sgt_gameid;
struct sgs_unit
{
	unsigned int idx;
	unsigned int idy;
	unsigned int idz;
	
	sgt_set value;
	sgt_set valuep;
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
void sgs_setvalue(sgt_set value,struct sgs_game *game,unsigned int x ,unsigned int y);
sgt_set sgs_getvalue(struct sgs_game *game,unsigned int x,unsigned int y);

sgt_set sgs_getvalue_px(struct sgs_game *game,unsigned int y);
sgt_set sgs_getvalue_py(struct sgs_game *game,unsigned int x);
sgt_set sgs_getvalue_pz(struct sgs_game *game,unsigned int x,unsigned int y);
sgt_set sgs_getvalue_p(struct sgs_game *game,unsigned int x,unsigned int y);

