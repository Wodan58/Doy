/*
    module  : do_tailrec.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void do_tailrec()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->op == typ_list
	   && stack->next->op == typ_list && stack->next->next->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next->next;
    for (;;) {
	cur = get(1);
	cur->op = typ_list;
	cur->list = stack;
	cur->next = dump1;
	dump1 = cur;
	exeterm(dump->list->next->next->list);
	num = stack->num;
	stack = dump1->list;
	dump1 = dump1->next;
	if (num) {
	    exeterm(dump->list->next->list);
	    break;
	}
	exeterm(dump->list->list);
    }
    dump = dump->next;
}
