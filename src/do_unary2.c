/*
    module  : do_unary2.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
unary2  :  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
void do_unary2()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next;
    exeterm(dump->list->list);
    cur = get(1);
    cur->op = stack->op;
    cur->val = stack->val;
    cur->next = dump1;
    dump1 = cur;
    cur = get(1);
    cur->op = dump->list->next->op;
    cur->val = dump->list->next->val;
    cur->next = dump->list->next->next->next;
    stack = cur;
    exeterm(dump->list->list);
    stack->next = dump1;
    dump1 = dump1->next;
    stack->next->next = dump->list->next->next->next;
    dump = dump->next;
}
