/*
    module  : do_trunc.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
void do_trunc()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = (int)trunc(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
