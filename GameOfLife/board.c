#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

board_t * make_board(int width, int height)
{
	int i,j,k;
	board_t *new_board = malloc(sizeof *new_board);
	if (new_board == NULL)
		return NULL;
	if((new_board->cells = malloc((width+2)*sizeof(int*))) == NULL) {
		free(new_board);
		return NULL;
	}
	for(i = 0; i < width+2; i++)
	{
		if((new_board->cells[i] = malloc((height+2) * sizeof(int))) == NULL) {
			for(k = 0; k < i; k++)
				free(new_board->cells[k]);
			free(new_board->cells);
			free(new_board);
			return NULL;
		}

		for( j = 0; j < height+2; j++)
			new_board->cells[i][j] = 0;
	}
	new_board->width = width;
	new_board->height = height;
	return new_board;
}

void fill_board(board_t *dest, file_t src)
{
	int i;
	
	for(i = 0; i < src.n; i++) /* n- number of pairs */
	{
		dest->cells[src.x[i]][src.y[i]] = 1;
	}
}

void show_board(board_t board)
{
	int i,j;
	printf("************");
	for(i = 0; i < board.height+2 ; i++)
	{
		for(j = 0; j < board.width+2; j++)
			printf("%c", ( board.cells[j][i] == 0 ? ' ' : 'X'  ));
		printf("\n");	
	}
}

void free_board(board_t *board)
{
	int i;
	for(i=0; i<board->width; i++)
		free(board->cells[i]);
	free(board->cells);
	free(board);
}




