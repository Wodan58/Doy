/*
    module  : do_sinh.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
sinh  :  F  ->  G
G is the hyperbolic sine of F.
*/
void do_sinh()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = sinh(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
