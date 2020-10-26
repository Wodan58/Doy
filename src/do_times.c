/*
    module  : do_times.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
times  :  N [P]  ->  ...
N times executes P.
*/
void do_times()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list &&
	   stack->next->op == typ_integer);
    if ((num = stack->next->num) == 0) {
	stack = stack->next->next;
	return;
    }
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next;
    while (num--)
	exeterm(dump->list->list);
    dump = dump->next;
}
