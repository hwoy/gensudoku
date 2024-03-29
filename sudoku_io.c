#include "sudoku_io.h"
#include <string.h>

static void replacech(char* str, char ch, char rp);
static void showgamedetail(FILE* fp, const struct sgs_game* game);

char sio_getch(char* buff, int size, char dkey)
{

    fgets(buff, size, stdin);
    replacech(buff, 13, 0);
    replacech(buff, 10, 0);
    if (!strlen(buff)) {
        return dkey;
    }
    return buff[0];
}

static void replacech(char* str, char ch, char rp)
{
    int i;
    for (i = 0; str[i]; i++) {
        if (str[i] == ch) {
            str[i] = rp;
        }
    }
}

static void showgamedetail(FILE* fp, const struct sgs_game* game)
{
    fprintf(fp, "ENGINE = v.%u.%u.%u, GAME = %u.%u, BID = %u, N_BLANK = %u\n\n", game->majorver, game->minorver, game->sminorver, game->bid, game->numblank, game->bid, game->numblank);
}

void printValuep(FILE* fp, struct sgs_game* game, char ch, char sch)
{
    unsigned int i, j, k;

    showgamedetail(fp, game);

    for (i = 0; i < S_SQR; i++) {
        if (!(i % S_ZSQR) && i)
            fprintf(fp, "\n");
        for (j = 0; j < S_SQR; j++) {
            if (!(j % S_ZSQR) && j)
                fprintf(fp, "\t");
            fprintf(fp, "[");
            for (k = 0; k < S_SQR; k++) {
                if (sgf_getvalue(game, j, i))
                    fputc(ch, fp);
                else if (sgf_getvalue_p(game, j, i) & POW2A(k))
                    fprintf(fp, "%u", k + 1);
                else
                    fputc(sgf_getvalue_p(game, j, i) ? ch : sch, fp);
            }
            fprintf(fp, "]");
        }
        fputc('\n', fp);
    }
}

void printFindvalueUnique(FILE* fp, struct sgs_game* game, char ch)
{
    unsigned int i, j, k;

    showgamedetail(fp, game);

    for (i = 0; i < S_SQR; i++) {
        if (!(i % S_ZSQR) && i)
            fprintf(fp, "\n");
        for (j = 0; j < S_SQR; j++) {
            if (!(j % S_ZSQR) && j)
                fprintf(fp, "\t");
            fprintf(fp, "[");

            if ((k = sgf_findvalueunique(game, j, i)))
                fprintf(fp, "%u", k);
            else
                fputc(ch, fp);

            fprintf(fp, "]");
        }
        fputc('\n', fp);
    }
}

void printFindvalueOne(FILE* fp, struct sgs_game* game, char ch)
{
    unsigned int i, j, k;

    showgamedetail(fp, game);

    for (i = 0; i < S_SQR; i++) {
        if (!(i % S_ZSQR) && i)
            fprintf(fp, "\n");
        for (j = 0; j < S_SQR; j++) {
            if (!(j % S_ZSQR) && j)
                fprintf(fp, "\t");
            fprintf(fp, "[");

            if ((k = sgf_findvalueone(game, j, i)))
                fprintf(fp, "%u", k);
            else
                fputc(ch, fp);

            fprintf(fp, "]");
        }
        fputc('\n', fp);
    }
}

void printBoard(FILE* fp, struct sgs_game* game, char ch, int shownblank)
{
    unsigned int i, j, k;
    if (shownblank)
        showgamedetail(fp, game);
    else
        fprintf(fp, "BID = %u\n\n", game->bid);

    for (i = 0; i < S_SQR; i++) {
        if (!(i % S_ZSQR) && i)
            fprintf(fp, "\n");
        for (j = 0; j < S_SQR; j++) {
            if (!(j % S_ZSQR) && j)
                fprintf(fp, "\t");
            fprintf(fp, "[");
            if ((k = sgf_getvalue(game, j, i)))
                fprintf(fp, "%u", k);
            else
                fputc(ch, fp);
            fprintf(fp, "]");
        }
        fputc('\n', fp);
    }
}

void genBoards(FILE* fp, struct sgs_game* game, sgt_bid bid, unsigned int num, char ch)
{
    unsigned int i;
    for (i = 0; i < num; i++) {
        sgf_setbid(game, i + bid);
        sgf_findboard(game);

        printBoard(fp, game, ch, 0);
        fputc('\n', fp);
    }
}

void genSudokus(FILE* fp, struct sgs_game* game, sgt_bid bid, unsigned int num, char ch)
{
    unsigned int i;
    for (i = 0; i < num; i++) {
        sgf_setbid(game, i + bid);
        sgf_createsudoku(game);

        printBoard(stdout, game, ch, 1);
        fputc('\n', fp);
    }
}

void genSudokus_rnd(FILE* fp, struct sgs_game* game, sgt_bid bid, unsigned int num, char ch, unsigned int sd, unsigned int seed)
{
    unsigned int i, j;
    j = sgf_getnblank(game);
    for (i = 0; i < num; i++) {
        sgf_seed(game, seed + i);
        sgf_setbid(game, bid + i);
        sgf_createsudoku_rnd(game, sd);
        fprintf(fp, "SN_BLANK_SEED = %u, SBID = %u, N_BLANK_SEED = %u, N = %u, SN_BLANK = %u, SD = %u\n", seed, bid, seed + i, num, j, sd);
        printBoard(fp, game, ch, 1);
        sgf_setnblank(game, j);
        fputc('\n', fp);
    }
}
