/*
    module  : do_cleave.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
void do_cleave()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next &&
	   stack->op == typ_list && stack->next->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next;
    exeterm(dump->list->next->list);
    cur = get(1);
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = dump1;
    dump1 = cur;
    stack = dump->list->next->next;
    exeterm(dump->list->list);
    stack->next = dump1;
    dump1 = dump1->next;
    stack->next->next = dump->list->next->next->next;
    dump = dump->next;
}
