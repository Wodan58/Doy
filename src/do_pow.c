/*
    module  : do_pow.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
pow  :  F G  ->  H
H is F raised to the Gth power.
*/
void do_pow()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_float &&
	   stack->next->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = pow(stack->next->dbl, stack->dbl);
    cur->next = stack->next->next;
    stack = cur;
}
