#ifndef _OPTIONS_H_
#define _OPTIONS_H_


enum results { ALL_CORRECT, N_NEGATIVE, UNKN_NEIGHB, UNKN_COLOR, FORBIDDEN_SYMBOLS, NAME_NULL, SCALE_NEGATIVE };

int check_args_and_opts(int n, char **p, char **q, char **s, int scale);
int is_forbidden_symbol_in(char *);
int unkn_neighb(char *);
char * my_strcpy(char * source);
int my_isdigit(char *w);

#endif
