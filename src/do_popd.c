/*
    module  : do_popd.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"

/*
popd  :  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
void do_popd()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = stack->next->next;
    stack = cur;
}
