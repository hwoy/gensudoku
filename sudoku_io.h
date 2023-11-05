#ifndef __SUDOKU_IO_H__
#define __SUDOKU_IO_H__

#include <stdio.h>
#include "sudoku.h"
char sio_getch(char* buff, int size, char dkey);
void printValuep(FILE* fp, struct sgs_game* game, char ch, char sch);
void printFindvalueUnique(FILE* fp, struct sgs_game* game, char ch);
void printFindvalueOne(FILE* fp, struct sgs_game* game, char ch);
void printBoard(FILE* fp, struct sgs_game* game, char ch, int shownblank);
void genBoards(FILE* fp, struct sgs_game* game, sgt_bid bid, unsigned int num, char ch);
void genSudokus(FILE* fp, struct sgs_game* game, sgt_bid bid, unsigned int num, char ch);
void genSudokus_rnd(FILE* fp, struct sgs_game* game, sgt_bid bid, unsigned int num, char ch, unsigned int sd, unsigned int seed);

#endif
