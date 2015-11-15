void printValuep(FILE *fp,struct sgs_game *game,char ch,char sch);
void printFindvalueUnique(FILE *fp,struct sgs_game *game,char ch);
void printFindvalueOne(FILE *fp,struct sgs_game *game,char ch);
void printBoard(FILE *fp,struct sgs_game *game,char ch);
void genBoards(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch);
void genSudokus(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch);
void genSudokus_rnd(FILE *fp,struct sgs_game *game,sgt_bid bid,unsigned int num,char ch,unsigned int sd,unsigned int seed);

