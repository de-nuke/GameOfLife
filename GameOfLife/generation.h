#ifndef _GENERATION_H_
#define _GENERATION_H_

#include <stdlib.h>
#include "board.h"
#include "makepng.h"

void generate(board_t *first, board_t *second, int n, char *prefix, char *suffix, char *neighb, int scale, char *dir);
int cell_dies(board_t b, int x, int y, char *neighb);
char *create_name(char *prefix, char* suffix, int counter, char *dir);
#endif
