#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

#include "coordinates.h"
#include "board.h"
#include "options.h"
#include "generation.h"

int main(int argc, char **argv)
{
	/* declarations of variables*/
	FILE *in = (argc > 1 && argv[1][0] != '-' ) ? fopen(argv[1], "r") : stdin;
	FILE *out = (argc > 2 && argv[2][0] != '-' ) ? fopen(argv[2], "w") : stdout;	
	file_t *xy;
	board_t *board;
	board_t *board2;
	int gen_num = 0;
	char *prefix = NULL;	
	char *suffix = NULL;
	char *neighb = NULL;
	int scale = 1;
	int c;
	int check_result;
	char *output, *input;

	/* checking files */
	if(in == NULL)
	{
		fprintf(stderr, "\n4 - No such file: %s\n", argv[1]);
		return 4;
	}
	if(out == NULL)
	{
		fprintf(stderr, "\n4 - Path doesn't exist:  %s\n", argv[2]);
		return 4;
	}	
	if(argc > 1) 
	{
		input = malloc((strlen(argv[1])+1) * sizeof(char));
		strcpy(input, argv[1]);
	}
	if(argc>2) 
	{
		output = malloc((strlen(argv[2])+1) * sizeof(char) );
		output = my_strcpy(argv[2]);
	}
	/* reading options */
	while((c = getopt (argc, argv, "n:p:q:s:x:")) != -1 )
		switch(c)
		{
		case 'n':
			if(my_isdigit(optarg))
				gen_num = atoi(optarg);
			else
			{
				fprintf(stderr, "\n3 - Option '-n' requires a number. [given: %s]\n", optarg);
				return 3;
			}
			break;
		case 'p':
			prefix = optarg;
			break;
		case 'q':
			suffix = optarg;
			break;
		case 's':
			neighb = optarg;
			break;
		case 'x':
			if(my_isdigit(optarg))
				scale = atoi(optarg);
			else
			{
				fprintf(stderr, "\n3- Option '-x' requires a number. [given: %s]\n", optarg);
				return 3;
			}
			break;
		case '?':
			if(optopt == 'n' || optopt == 'p' || optopt == 'q' || optopt == 's' || optopt == 'x')
				fprintf(stderr, "\n3 - Option -%c requires an argument. \n", optopt);
			else if(isprint (optopt))
				fprintf(stderr, "\n3 - Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "\n3 - Unknown option character `\\x%x'. \n", optopt);
			return 3; /* = EXIT_FAILURE */
		default:
			abort();
		}
	/* checking options */
	check_result = check_args_and_opts(gen_num, &prefix, &suffix, &neighb, scale);	
	switch(check_result)
	{
	case ALL_CORRECT:
		break;
	case N_NEGATIVE: 
		fprintf(stderr, "\n3 -Argument of '-n' option must be a positive number" 
			"[given: -n %d].\n", gen_num);
		return 3; /* = EXIT_FAILURE */
	case FORBIDDEN_SYMBOLS:
		fprintf(stderr, "\n3 - Prefix or suffix cannot contain any of the following characters:"
			" \\ / : * ? \" < > | \n");
		return 3; /* = EXIT_FAILURE */
	case UNKN_NEIGHB:
		fprintf(stderr, "\n3 - Unknown neighbourhood: \"%s\".\n"
			"Avaible: \"Moore\", \"Neumann\" (capitalization doesn't matter)\n", neighb );
		return 3; /* = EXIT_FAILURE */
	case SCALE_NEGATIVE:
		fprintf(stderr, "\n3 - Argument of '-x' option must be a positive number[given: x = %d].\n"
			"Example: -x10 makes generation 10 times larger.", scale);
		return 3; /* = EXIT_FAILURE */
	default:
		abort();
	}
	
	/* initializing structures */
	if((xy = make_coords(in)) == NULL)
	{
		fprintf(stderr, "\n2 - Can't load data from file \"%s\". It is corrupt or contains wrong data format.\n"
			"The input data should be positive integers.\n"
			"The first two numbers are respectively: width and height. Then, there are pairs \"x y\".\n"
			"'x' must be greater than 0 and smaller than 'width'.\n"
			"'y' must be greater than 0 and smaller than 'height'.\n\n",input);
		if(in != NULL) fclose(in);
		if(out != NULL) fclose(out);
		return 2; /* = EXIT_FAILURE */
	}
	if( ((board = make_board(xy->width, xy->height)) == NULL) || ((board2 = make_board(xy->width, xy->height)) == NULL ))
	{
		fprintf(stderr, "\n1 - LINE: 116, \"make_board\" function: Can't alocate memory");
		if(in != NULL) fclose(in);
		if(out != NULL) fclose(out);
		return 1;
	}


	fill_board(board, *xy);
	
	generate(board, board2, gen_num, prefix, suffix, neighb, scale, output); /* includes creating png files. */

	write_to_file(board->width, board->height, board->cells, out);

	free_coords(xy);
	free_board(board);
	free_board(board2);
	if(fclose(in) != 0) return EXIT_FAILURE; 
	if(fclose(out) != 0) return EXIT_FAILURE;
	return EXIT_SUCCESS;
}




