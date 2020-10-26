/*
    module  : do_fwrite.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "chars.h"

/*
fwrite  :  S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
void do_fwrite()
{
    int i;
    char *str;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list &&
	   stack->next->op == typ_file && stack->next->fp);
    str = malloc(MAXSTR);
    for (i = 0, cur = stack->list; cur; cur = cur->next) {
	assert(cur->op == typ_integer);
	str[i++] = cur->num;
	if (i == MAXSTR)
	    str = realloc(str, i + MAXSTR);
    }
    stack = stack->next;
    fwrite(str, 1, i, stack->fp);
    free(str);
}
