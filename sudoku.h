#ifndef __SUDOKU_H__
#define __SUDOKU_H__

#define S_ZSQR 3
#define S_SQR (S_ZSQR * S_ZSQR)

#define POW2A(x) (1 << (x))

#define SUDOKU_ENGINE_MAJOR_VERSION 1
#define SUDOKU_ENGINE_MINOR_VERSION 1
#define SUDOKU_ENGINE_SMINOR_VERSION 0

#include "glibcrng.h"

typedef unsigned short sgt_set;
typedef unsigned int sgt_bid;
struct sgs_unit {
    unsigned int idx;
    unsigned int idy;
    unsigned int idz;

    sgt_set value;
};

struct sgs_board {
    struct sgs_unit unit[S_SQR][S_SQR];
};

struct sgs_game {
    GLIBCRNG rng;
    sgt_bid bid;
    unsigned int numblank;
    struct sgs_board board;

    unsigned int majorver;
    unsigned int minorver;
    unsigned int sminorver;
};

struct sgs_game* sgf_init(struct sgs_game* game, sgt_bid bid, unsigned int numblank);
void sgf_setvalue(sgt_set value, struct sgs_game* game, unsigned int x, unsigned int y);
sgt_set sgf_getvalue(const struct sgs_game* game, unsigned int x, unsigned int y);
void sgf_setbid(struct sgs_game* game, unsigned int bid);

sgt_set sgf_getvalue_x(const struct sgs_game* game, unsigned int y);
sgt_set sgf_getvalue_y(const struct sgs_game* game, unsigned int x);
sgt_set sgf_getvalue_z(const struct sgs_game* game, unsigned int x, unsigned int y);
sgt_set sgf_getvalue_p(const struct sgs_game* game, unsigned int x, unsigned int y);

unsigned int sgf_countvalue_set(sgt_set value);
unsigned int sgf_countvalue(const struct sgs_game* game, unsigned int x, unsigned int y);

void sgf_seed(struct sgs_game* game, URND32 seed);
unsigned int sgf_rand(struct sgs_game* game);
unsigned int sgf_random(struct sgs_game* game, unsigned int min, unsigned int max);

unsigned int sgf_log2a(unsigned int num);
unsigned int sgf_findvalueone(const struct sgs_game* game, unsigned int x, unsigned int y);
unsigned int sgf_findvalueunique(const struct sgs_game* game, unsigned int x, unsigned int y);
unsigned int sgf_getobstruct(const struct sgs_game* game);
int sgf_genboard(struct sgs_game* game);
int sgf_completeboard(const struct sgs_game* game);
void sgf_resetboard(struct sgs_game* game);
sgt_bid sgf_findboard(struct sgs_game* game); /*take sgf_srandom*/
void sgf_setbid(struct sgs_game* game, sgt_bid bid);
sgt_bid sgf_getbid(const struct sgs_game* game);
void sgf_createsudoku(struct sgs_game* game);
void sgf_createsudoku_rnd(struct sgs_game* game, unsigned int sd); /*No sgf_srandom and Modify numblank*/

void sgf_setnblank(struct sgs_game* game, unsigned int numblank);
unsigned int sgf_getnblank(const struct sgs_game* game);

#endif
