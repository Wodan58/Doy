/*
    module  : do_choice.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"

/*
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
void do_choice()
{
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next);
    cur = get(1);
    node = stack->next->next;
    if (node->num)
	stack = stack->next;
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = node->next;
    stack = cur;
}
