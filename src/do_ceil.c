/*
    module  : do_ceil.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
ceil  :  F  ->  G
G is the float ceiling of F.
*/
void do_ceil()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = ceil(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
