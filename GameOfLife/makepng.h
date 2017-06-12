#ifndef _MAKEPNG_H_
#define _MAKEPNG_H_

#include <png.h>

void write_png_file(char* file_name);

void process_file(int w, int h, int **cells, int scale);

#endif
