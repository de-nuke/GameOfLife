#include <stdlib.h>
#include <stdio.h>

#include "coordinates.h"

file_t * make_coords(FILE *in)
{	
	int i = 0;
	int size;
	file_t * new_coords = malloc(sizeof *new_coords);
	if(new_coords == NULL)
		return NULL;
	new_coords->n = 0;

	if(fscanf(in, "%d", &(new_coords->width)) != 1 ) {
		free(new_coords);
		return NULL;
	}
	else if(new_coords->width < 1 || new_coords->width > MAX_WIDTH ) {
		free(new_coords);
		return NULL;
	}

	if(fscanf(in, "%d", &(new_coords->height)) != 1 ) {
		free(new_coords);
		return NULL;
	}

	else if(new_coords->height < 1 || new_coords->height > MAX_HEIGHT ) {
		free(new_coords);
		return NULL;
	}
	size = (new_coords->height * new_coords->width);
	printf("%d \n",size);
	if((new_coords->x = malloc(size *sizeof(int) )) == NULL) {
		free(new_coords);
		return NULL;
	}
	if((new_coords->y = malloc( size*sizeof(int) )) == NULL) {
		free(new_coords->x);
		free(new_coords);
		return NULL;
	}
	
	while(fscanf(in, "%d %d", new_coords->x+i, new_coords->y+i) != EOF && new_coords->n < size)
	{
		/*if(new_coords->n > size); {
			printf("%d ", size);
			return new_coords; }
		*/
		if(new_coords->x[i] <= 0 || new_coords->x[i] > new_coords->width ||
		   new_coords->y[i] <= 0 || new_coords->y[i] > new_coords->height)
		{
			free(new_coords->y); free(new_coords->x); free(new_coords);
			return NULL;	
		}
		i++;
		new_coords->n++;
	}
	printf("%d \n", size);
	return new_coords;

}

void write_to_file(int width, int height, int **cells, FILE *out)
{
	int i,j;
	fprintf(out, "%d\n", width);
	fprintf(out, "%d\n", height);

	for(i = 0 ; i < width; i++)
		for(j = 0; j < height; j++)
		{
			if(cells[i][j] == 1) 
				fprintf(out, "%d %d\n", i, j);
		}
	printf("Successfully writen last generation to file.\n");		
}

void free_coords(file_t *xy)
{
	free(xy->x);
	free(xy->y);
	free(xy);
}
