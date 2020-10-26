/*
    module  : do_swap.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"

/*
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
void do_swap()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(2);
    cur[1].op = stack->op;
    cur[1].val = stack->val;
    stack = stack->next;
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = &cur[1];
    cur[1].next = stack->next;
    stack = cur;
}
