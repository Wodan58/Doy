/*
    module  : do_nullary.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
nullary  :  [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
void do_nullary()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next;
    exeterm(dump->list->list);
    cur = get(1);
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = dump->list->next;
    stack = cur;
    dump = dump->next;
}
