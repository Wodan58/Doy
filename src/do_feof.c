/*
    module  : do_feof.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
void do_feof()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = feof(stack->fp);
    cur->next = stack;
    stack = cur;
}
