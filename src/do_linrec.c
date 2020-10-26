/*
    module  : do_linrec.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
static void aux_linrec()
{
    int num;
    data_t *cur;

    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump1;
    dump1 = cur;
    exeterm(dump->list->next->next->next->list);
    num = stack->num;
    stack = dump1->list;
    dump1 = dump1->next;
    if (num)
	exeterm(dump->list->next->next->list);
    else {
	exeterm(dump->list->next->list);
	put(-1);
	proc(dump->list->list);
	put((long)aux_linrec);
    }
}

void do_linrec()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->next->next->next
	   && stack->op == typ_list && stack->next->op == typ_list &&
	   stack->next->next->op == typ_list &&
	   stack->next->next->next->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next->next->next;
    num = used();
    aux_linrec();
    while (num < used())
	loop();
    dump = dump->next;
}
