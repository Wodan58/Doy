/*
    module  : do_construct.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
construct  :  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
void do_construct()
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
    stack = stack->next->next;
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;				// save old stack
    cur->next = dump1;
    dump1 = cur;
    exeterm(dump->list->next->list);		// [P]
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;				// save current stack
    cur->next = dump2;
    dump2 = cur;
    cur = get(1);
    cur->op = typ_list;
    cur->list = dump->list->list;		// [[P1] [P2] ..]
    cur->next = dump3;
    dump3 = cur;
    while (dump3->list) {
	stack = dump2->list;
	exeterm(dump3->list->list);
	stack->next = dump1->list;
	dump1->list = stack;
	dump3->list = dump3->list->next;
    }
    dump3 = dump3->next;
    dump2 = dump2->next;
    stack = dump1->list;
    dump1 = dump1->next;
    dump = dump->next;
}
