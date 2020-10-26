/*
    module  : do_branch.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
branch  :  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
void do_branch()
{
    int num;
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
    num = stack->num;
    stack = stack->next;
    exeterm(num ? dump->list->next->list : dump->list->list);
    dump = dump->next;
}
