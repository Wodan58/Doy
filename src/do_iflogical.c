/*
    module  : do_iflogical.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
iflogical  :  X [T] [E]  ->  ...
If X is a logical or truth value, executes T else executes E.
*/
void do_iflogical()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->op == typ_list
	   && stack->next->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next;
    if (stack->op == typ_logical)
	exeterm(dump->list->next->list);
    else
	exeterm(dump->list->list);
    dump = dump->next;
}
