/*
    module  : do_ldexp.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
ldexp  :  F I  ->  G
G is F times 2 to the Ith power.
*/
void do_ldexp()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_integer &&
	   stack->next->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = ldexp(stack->next->dbl, stack->num);
    cur->next = stack->next->next;
    stack = cur;
}
