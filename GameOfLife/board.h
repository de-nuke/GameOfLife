#ifndef _BOARD_H_
#define _BOARD_H_

#include "coordinates.h"

typedef struct e {

	int width;
	int height;
	int **cells;
} board_t;

board_t * make_board2(int width, int height);
board_t * make_board(int width, int height);
void fill_board(board_t *dest, file_t src);
void free_board(board_t *board);
void show_board(board_t board);

#endif
