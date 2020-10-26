/*
    module  : do_atan.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
atan  :  F  ->  G
G is the arc tangent of F.
*/
void do_atan()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = atan(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
