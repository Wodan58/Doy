/*
    module  : do_ferror.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
ferror  :  S  ->  S B
B is the error status of stream S.
*/
void do_ferror()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = ferror(stack->fp);
    cur->next = stack;
    stack = cur;
}
