/*
    module  : do_ftell.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
ftell  :  S  ->  S I
I is the current position of stream S.
*/
void do_ftell()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = ftell(stack->fp);
    cur->next = stack;
    stack = cur;
}
