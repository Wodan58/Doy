/*
    module  : do_fgets.c
    version : 1.3
    date    : 02/22/21
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
    data_t *cur;
    char *str, *ptr;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    str = malloc(MAXSTR);
    str[i = 0] = 0;
    while (fgets(str + i, MAXSTR, stack->fp)) {
	if ((i = strlen(str)) > 0 && str[i - 1] == '\n')
	    break;
	if ((ptr = realloc(str, i + MAXSTR)) == 0)
	    break;
	str = ptr;
    }
    cur = get(1);
    cur->op = typ_string;
    cur->str = str;
    cur->next = stack;
    stack = cur;
}
