#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "generation.h"

void generate(board_t *first, board_t *second, int n, char *prefix, char *suffix, char *neighb, int scale, char *dir)
{
	int i,j;
	int counter = 0;
	char *filename;
	char *path = NULL;
	board_t *temp;

	if(dir != NULL && dir[0] != '-')
	{
		path = malloc((strlen("pictures/") + strlen(dir) + 2) * sizeof(char));
		strcpy(path, "pictures/");
		strcat(path, dir);
		strcat(path, "/");
		mkdir(path, 0777);
	}	
	do
	{
		/* show_board(*first); */ /*write on console */
		filename = create_name(prefix, suffix, counter, path);
		process_file(first->width, first->height, first->cells, scale);
		write_png_file(filename);

		for(i = 1; i < first->width+1; i++)
		 for(j = 1; j < first->height+1; j++)
		 {
			if(cell_dies(*first, i, j, neighb)) second->cells[i][j] = 0;
			else second->cells[i][j] = 1;
		 }
	
	counter++;	
	
	temp = first;
	first = second;
	second = temp;
	}while(n--);
	printf("Successfully generated %d pictures.\n", counter-1); 

}

int cell_dies(board_t board, int x, int y, char *neighb)
{
	int neighb_n = 0;
				
		neighb_n += board.cells[x][y+1] + board.cells[x-1][y] + board.cells[x+1][y] + board.cells[x][y-1];
		if( strcmp(neighb, "moore" ) == 0 )
			neighb_n += board.cells[x-1][y+1] + board.cells[x+1][y+1] + board.cells[x-1][y-1] + board.cells[x+1][y-1];
	
	if(board.cells[x][y] == 1)
		if(neighb_n == 2 || neighb_n == 3) return 0;
		else return 1;
	else 
		if(neighb_n == 3) return 0;
		else return 1;
}

char *create_name(char *prefix, char *suffix, int counter, char *path)
{	
	char *w = malloc(5*sizeof(char));
	char *c = malloc(5*sizeof(char)); 
	char *name;
	char *number;
	strcpy(w, "LAST");
	if(counter > 9999) return w;
	
	number = malloc(10 * sizeof (char));
	if(counter < 10) strcpy(number, "000"); 
	if(counter >= 10 && counter <100) strcpy(number, "00");
	if(counter >=100 && counter < 1000) strcpy(number, "0");
	if(counter >= 1000 && counter < 10000) strcpy(number, "");

	sprintf(c, "%d", counter);
	strcat(number, c);
	if(path != NULL) 
	{
	  name = malloc( (strlen(path)+strlen(prefix)+strlen(number)+strlen(suffix)+5) * sizeof (char) );
	  strcpy(name, path);
	}
	else
	{
	  name = malloc( (10+strlen(prefix)+strlen(number)+strlen(suffix)+5) * sizeof(char));
	  strcpy(name, "pictures/");	
	}
	strcat(name, prefix);
	strcat(name, number);
	strcat(name, suffix);
	strcat(name, ".png\0");

	return name;
}





