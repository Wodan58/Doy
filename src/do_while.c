/*
    module  : do_while.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
void do_while()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list &&
	   stack->next->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    for (;;) {
	stack = dump->list->next->next;
	exeterm(dump->list->next->list);
	if (!stack->num)
	    break;
	stack = dump->list->next->next;
	exeterm(dump->list->list);
	dump->list->next->next = stack;
    }
    stack = dump->list->next->next;
    dump = dump->next;
}
