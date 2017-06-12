#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "options.h"

int is_forbidden_symbol_in(char *p)
{
	int i;
	char symbol[10] = {'\\', '/', ':', '*', '?', '|', '<', '>', '\"', '\0'};
	for(i = 0; i < 10; i++)
		if(memchr(p, symbol[i], strlen(p)) != NULL)
			return 1;
	return 0;
}

int unkn_neighb(char *s)
{
	int i;

	char *str = s;
	for(i = 0; str[i]; i++)
	{
		str[i] = tolower(str[i]);
	}
	if(strcmp(str, "moore") != 0 && strcmp(str, "neumann") != 0)
		return 1;
	return 0;
}

int check_args_and_opts(int n, char **p, char **q, char **s, int scale)
{
	if(n < 0)
		return N_NEGATIVE;
	
	if(*p == NULL)
	{	
		*p = malloc(8);
		strcpy(*p, "picture");
	}
	if(*q == NULL)
	{
		*q = malloc(1*sizeof(char));
		strcpy(*q, "");
	}
	
	if(is_forbidden_symbol_in(*p) || is_forbidden_symbol_in(*q))
		return FORBIDDEN_SYMBOLS;
	if(*s == NULL)
	{
		*s = malloc(6);
		strcpy(*s, "moore");
	}
	else if(unkn_neighb(*s))	
		return UNKN_NEIGHB;
	if(scale < 0)
		return SCALE_NEGATIVE;
		
	return ALL_CORRECT;
}

char * my_strcpy(char * source)
{
	char *w;
	char *c = malloc(strlen(source));
	w = strtok(source, "/");
	if(w == NULL)
		return source;
	else
		while(w != NULL)
		{
			strcpy(c, w);
			w = strtok(NULL, "/");	
		}
	
	if(c != NULL)
		return c;

	return NULL;
}

int my_isdigit(char *w)
{
	int i = 0;
	int was_minus_before = 0;
	while(w[i] != '\0')
	{
		if( !isdigit(w[i]) )
		{ 
			if(w[i] != '-') 
				return 0;
			else if(was_minus_before)
				 return 0;
			else 
				was_minus_before = 1; 
		}
		i++;
	}
	return 1;
}
