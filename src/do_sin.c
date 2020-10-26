/*
    module  : do_sin.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
sin  :  F  ->  G
G is the sine of F.
*/
void do_sin()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = sin(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
