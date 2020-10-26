/*
    module  : do_fgets.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "chars.h"

/*
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
void do_fgets()
{
    int i;
    char *str;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    str = malloc(MAXSTR);
    str[i = 0] = 0;
    while (fgets(str + i, MAXSTR, stack->fp)) {
	if ((i = strlen(str)) > 0 && str[i - 1] == '\n')
	    break;
	str = realloc(str, i + MAXSTR);
    }
    cur = get(1);
    cur->op = typ_string;
    cur->str = str;
    cur->next = stack;
    stack = cur;
}
