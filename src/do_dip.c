/*
    module  : do_dip.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
void do_dip()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next;
    exeterm(dump->list->list);
    cur = get(1);
    cur->op = dump->list->next->op;
    cur->val = dump->list->next->val;
    cur->next = stack;
    stack = cur;
    dump = dump->next;
}
