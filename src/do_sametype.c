/*
    module  : do_sametype.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
sametype  :  X Y  ->  B
Tests whether X has the same type as Y.
*/
void do_sametype()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->next->op == stack->op;
    if (cur->num && stack->op == typ_symbol)
	cur->num = stack->next->num == stack->num;
    cur->next = stack->next->next;
    stack = cur;
}
