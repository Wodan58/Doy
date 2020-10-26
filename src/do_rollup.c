/*
    module  : do_rollup.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"

/*
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
void do_rollup()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next);
    cur = get(3);
    cur[2].op = stack->op;
    cur[2].val = stack->val;
    stack = stack->next;
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = &cur[1];
    stack = stack->next;
    cur[1].op = stack->op;
    cur[1].val = stack->val;
    cur[1].next = &cur[2];
    cur[2].next = stack->next;
    stack = cur;
}
