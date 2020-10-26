/*
    module  : do_tan.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "ident.h"

/*
tan  :  F  ->  G
G is the tangent of F.
*/
void do_tan()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack->op == typ_float);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = tan(stack->dbl);
    cur->next = stack->next;
    stack = cur;
}
