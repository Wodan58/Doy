/*
    module  : do_app1.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
app1  :  X [P]  ->  R
Executes P, pushes result R on stack with X.
*/
void do_app1()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next;
    exeterm(dump->list->list);
    dump = dump->next;
}
