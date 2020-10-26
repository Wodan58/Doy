/*
    module  : do_float.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
float  :  R  ->  B
Tests whether R is a float.
*/
void do_float()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->op == typ_float;
    cur->next = stack->next;
    stack = cur;
}
