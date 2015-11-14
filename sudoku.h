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
	unsigned int numstart;
	struct sgs_board board;
	const char *playername;
};

struct sgs_game *sgf_init(struct sgs_game *game,const char *playername,sgt_gameid gameid,unsigned int numstart);
void sgf_setvalue(sgt_set value,struct sgs_game *game,unsigned int x ,unsigned int y);
sgt_set sgf_getvalue(struct sgs_game *game,unsigned int x,unsigned int y);

sgt_set sgf_getvalue_x(struct sgs_game *game,unsigned int y);
sgt_set sgf_getvalue_y(struct sgs_game *game,unsigned int x);
sgt_set sgf_getvalue_z(struct sgs_game *game,unsigned int x,unsigned int y);
sgt_set sgf_getvalue_p(struct sgs_game *game,unsigned int x,unsigned int y);

unsigned int sgf_countvalue_set(sgt_set value);
unsigned int sgf_countvalue(struct sgs_game *game,unsigned int x,unsigned int y);

int sgf_random (int min, int max);
unsigned int sgf_log2a (unsigned int num);
unsigned int sgf_findvalueone(struct sgs_game *game,unsigned int x,unsigned int y);
unsigned int sgf_findvalueunique(struct sgs_game *game,unsigned int x,unsigned int y);
unsigned int sgf_getobstruct(struct sgs_game *game);
void sgf_genboard(struct sgs_game *game);

