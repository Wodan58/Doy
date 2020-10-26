/*
    module  : do_index.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
index  :  B L  ->  X
X (= L[B]) is the 1st or 2nd member of list L.
*/
void do_index()
{
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list && stack->list);
    cur = get(1);
    node = stack->next->num ? stack->list->next : stack->list;
    cur->op = node->op;
    cur->val = node->val;
    cur->next = stack->next->next;
    stack = cur;
}
