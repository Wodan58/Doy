/*
    module  : do_frexp.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
void do_frexp()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(2);
    cur->op = typ_integer;
    cur[1].dbl = frexp(stack->dbl, &num);
    cur->num = num;
    cur->next = &cur[1];
    cur[1].op = typ_float;
    cur[1].next = stack->next;
    stack = cur;
}
