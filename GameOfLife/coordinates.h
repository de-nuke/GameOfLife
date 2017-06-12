#ifndef _STRUCT_H_
#define _STRUCT_H_

#define MAX_WIDTH 300
#define MAX_HEIGHT 300

#include <stdio.h>

typedef struct s {
    int height, width;
    int *x; /* keeps x-coordinates */
    int *y; /* keeps y-coordinates */
    int n;
} file_t;


file_t * make_coords(FILE *in);
void show_struct(file_t xy);
void write_to_file(int width, int height, int **cells, FILE *out);
void free_coords(file_t *xy);

#endif
