/*
    module  : do_fwrite.c
    version : 1.3
    date    : 02/22/21
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
    data_t *cur;
    char *str, *ptr;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list &&
	   stack->next->op == typ_file && stack->next->fp);
    str = malloc(MAXSTR);
    for (i = 0, cur = stack->list; cur; cur = cur->next) {
	assert(cur->op == typ_integer);
	str[i++] = cur->num;
	if (i % MAXSTR == 0) {
	    if ((ptr = realloc(str, i + MAXSTR)) == 0)
		break;
	    str = ptr;
	}
    }
    stack = stack->next;
    fwrite(str, 1, i, stack->fp);
    free(str);
}
