/*
    module  : do_cond.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "boole.h"

/*
cond  :  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
void do_cond()
{
    data_t *cur;
    int num = FALSE;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list && stack->list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack->list;
    cur->next = dump1;
    dump1 = cur;
    while (!num && dump1->list && dump1->list->next) {
	stack = dump->list->next;
	exeterm(dump1->list->list->list);
	if ((num = stack->num) == FALSE)
	    dump1->list = dump1->list->next;
    }
    stack = dump->list->next;
    if (num)
	exeterm(dump1->list->list->next);
    else
	exeterm(dump1->list->list);
    dump1 = dump1->next;
    dump = dump->next;
}
