/*
    module  : do_exp.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
exp  :  F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
void do_exp()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = exp(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
