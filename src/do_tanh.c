/*
    module  : do_tanh.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
tanh  :  F  ->  G
G is the hyperbolic tangent of F.
*/
void do_tanh()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = tanh(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
