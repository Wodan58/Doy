/*
    module  : do_dup.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"

/*
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
void do_dup()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = stack;
    stack = cur;
}
