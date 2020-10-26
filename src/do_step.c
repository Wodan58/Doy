/*
    module  : do_step.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "set32.h"

/*
step  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void do_step()
{
    int i, j;
    char *str;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next->next;
    switch (dump->list->next->op) {
    case typ_set :
	j = dump->list->next->num;
	for (i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i)) {
		cur = get(1);
		cur->op = typ_integer;
		cur->num = i;
		cur->next = stack;
		stack = cur;
		exeterm(dump->list->list);
	    }
	break;

    case typ_string :
	for (str = dump->list->next->str; *str; str++) {
	    cur = get(1);
	    cur->op = typ_char;
	    cur->num = *str;
	    cur->next = stack;
	    stack = cur;
	    exeterm(dump->list->list);
	}
	break;

    case typ_list :
	cur = get(1);
	cur->op = typ_list;
	cur->list = dump->list->next->list;
	cur->next = dump1;
	dump1 = cur;
	while (dump1->list) {
	    cur = get(1);
	    cur->op = dump1->list->op;
	    cur->val = dump1->list->val;
	    cur->next = stack;
	    stack = cur;
	    exeterm(dump->list->list);
	    dump1->list = dump1->list->next;
	}
	dump1 = dump1->next;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    dump = dump->next;
}
