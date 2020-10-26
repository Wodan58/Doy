/*
    module  : do_fgetch.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
void do_fgetch()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    cur = get(1);
    cur->op = typ_char;
    cur->num = fgetc(stack->fp);
    cur->next = stack;
    stack = cur;
}
