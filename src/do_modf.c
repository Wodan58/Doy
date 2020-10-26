/*
    module  : do_modf.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
void do_modf()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_float);
    cur = get(2);
    cur->op = typ_float;
    cur[1].dbl = modf(stack->dbl, &cur->dbl);
    cur->next = &cur[1];
    cur[1].op = typ_float;
    cur[1].next = stack->next;
    stack = cur;
}
