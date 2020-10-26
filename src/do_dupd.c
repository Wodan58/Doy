/*
    module  : do_dupd.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"

/*
dupd  :  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
void do_dupd()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(3);
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = &cur[1];
    stack = stack->next;
    cur[2].op = cur[1].op = stack->op;
    cur[2].val = cur[1].val = stack->val;
    cur[1].next = &cur[2];
    cur[2].next = stack->next;
    stack = cur;
}
