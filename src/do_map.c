/*
    module  : do_map.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "set32.h"

/*
map  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void do_map()
{
    data_t *cur;
    int i, j, k;
    char *str, *ptr;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next;
    switch (stack->op) {
    case typ_set :
	for (j = stack->num, k = i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i)) {
		cur = get(1);
		cur->op = typ_integer;
		cur->val = i;
		cur->next = dump->list->next->next;
		stack = cur;
		exeterm(dump->list->list);
		k = set_bit(k, stack->num);
	    }
	cur = get(1);
	cur->op = typ_set;
	cur->num = k;
	cur->next = dump->list->next->next;
	stack = cur;
	break;

    case typ_string :
	for (ptr = stack->str, str = strdup(ptr), i = 0; *ptr; ptr++) {
	    cur = get(1);
	    cur->op = typ_char;
	    cur->num = *ptr;
	    cur->next = dump->list->next->next;
	    stack = cur;
	    exeterm(dump->list->list);
	    str[i++] = stack->num;
	}
	cur = get(1);
	cur->op = typ_string;
	cur->str = str;
	cur->next = dump->list->next->next;
	stack = cur;
	break;

    case typ_list :
	cur = get(1);
	cur->op = typ_list;
	cur->list = stack->list;
	cur->next = dump1;
	dump1 = cur;
	cur = get(1);
	cur->op = typ_list;
	cur->list = 0;
	cur->next = dump2;
	dump2 = cur;
	cur = get(1);
	cur->op = typ_list;
	cur->list = 0;
	cur->next = dump3;
	dump3 = cur;
	while (dump1->list) {
	    cur = get(1);
	    cur->op = dump1->list->op;
	    cur->val = dump1->list->val;
	    cur->next = dump->list->next->next;
	    stack = cur;
	    exeterm(dump->list->list);
	    assert(stack);
	    cur = get(1);
	    cur->op = stack->op;
	    cur->val = stack->val;
	    cur->next = 0;
	    if (!dump2->list)
		dump3->list = dump2->list = cur;
	    else
		dump3->list = dump3->list->next = cur;
	    dump1->list = dump1->list->next;
	}
	cur = get(1);
	cur->op = typ_list;
	cur->list = dump2->list;
	cur->next = dump->list->next->next;
	stack = cur;
	dump3 = dump3->next;
	dump2 = dump2->next;
	dump1 = dump1->next;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    dump = dump->next;
}
