/*
    module  : do_condlinrec.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
condlinrec  :  [ [C1] [C2] .. [D] ]  ->  ...
Each [Ci] is of the form [[B] [T]] or [[B] [R1] [R2]].
Tries each B. If that yields true and there is just a [T], executes T and exit.
If there are [R1] and [R2], executes R1, recurses, executes R2.
Subsequent case are ignored. If no B yields true, then [D] is used.
It is then of the form [[T]] or [[R1] [R2]]. For the former, executes T.
For the latter executes R1, recurses, executes R2.
*/
static void aux_condlinrec()
{
    int num = 0;
    data_t *cur;

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
    if (num) {
	exeterm(dump1->list->list->next->list);
	if (dump1->list->list->next->next) {
	    put(-1);
	    proc(dump1->list->list->next->next->list);
	    put((long)aux_condlinrec);
	}
    } else {
	exeterm(dump1->list->list->list);
	if (dump1->list->list->next) {
	    put(-1);
	    proc(dump1->list->list->next->list);
	    put((long)aux_condlinrec);
	}
    }
    dump1 = dump1->next->next;
}

void do_condlinrec()
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
    aux_condlinrec();
    while (num < used())
	loop();
    dump = dump->next;
}
