/*
    module  : do_logical.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
logical  :  X  ->  B
Tests whether X is a logical.
*/
void do_logical()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->op == typ_logical;
    cur->next = stack->next;
    stack = cur;
}
