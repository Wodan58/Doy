/*
    module  : do_floor.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
floor  :  F  ->  G
G is the floor of F.
*/
void do_floor()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = floor(stack->dbl);
    cur->next = stack;
    stack = cur;
}
