/*
    module  : do_condnestrec.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
condnestrec  :  [ [C1] [C2] .. [D] ]  ->  ...
A generalisation of condlinrec.
Each [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form
[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].
For the case taken, executes each [Ri] but recurses between any two
consecutive [Ri] (n > 3 would be exceptional.)
*/
static void aux_condnestrec()
{
    data_t *cur;
    int pos, num = 0;

    cur = get(2);
    cur->op = typ_list;
    cur->list = dump->list->list;
    cur->next = &cur[1];
    cur[1].op = typ_list;
    cur[1].list = stack;
    cur[1].next = dump1;
    dump1 = cur;
    while (!num && dump1->list && dump1->list->next) {
	stack = dump1->next->list;
	exeterm(dump1->list->list->list);
	if ((num = stack->num) == 0)
	    dump1->list = dump1->list->next;
    }
    stack = dump1->next->list;
    dump1->next->list = num ? dump1->list->list->next : dump1->list->list;
    exeterm(dump1->next->list->list);
    num = used();
    while ((dump1->next->list = dump1->next->list->next) != 0) {
	put((long)aux_condnestrec);
	pos = used();
	proc(dump1->next->list->list);
	rev(pos, used() - 1);
    }
    rev(num, used() - 1);
    dump1 = dump1->next->next;
}

void do_condnestrec()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list && stack->list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next;
    num = used();
    aux_condnestrec();
    while (num < used())
	loop();
    dump = dump->next;
}
