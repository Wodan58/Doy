/*
    module  : do_split.c
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
split  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void do_split()
{
    data_t *cur;
    int i, j, k, l;
    char *str, *buf, *ptr;

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
	for (j = stack->num, l = k = i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i)) {
		cur = get(1);
		cur->op = typ_integer;
		cur->num = i;
		cur->next = dump->list->next->next;
		exeterm(dump->list->list);
		if (stack->num)
		    k = set_bit(k, i);
		else
		    l = set_bit(l, i);
	    }
	cur = get(2);
	cur->op = typ_set;
	cur->num = l;
	cur->next = &cur[1];
	cur[1].op = typ_set;
	cur[1].num = k;
	cur[1].next = dump->list->next->next;
	stack = cur;
	break;

    case typ_string :
	ptr = stack->str;
	str = strdup(ptr);
	buf = strdup(ptr);
	for (j = i = 0; *ptr; ptr++) {
	    cur = get(1);
	    cur->op = typ_char;
	    cur->num = *ptr;
	    cur->next = dump->list->next->next;
	    stack = cur;
	    exeterm(dump->list->list);
	    if (stack->num)
		str[i++] = *ptr;
	    else
		buf[j++] = *ptr;
	}
	str[i] = 0;
	buf[j] = 0;
	cur = get(2);
	cur->op = typ_string;
	cur->str = buf;
	cur->next = &cur[1];
	cur[1].op = typ_string;
	cur[1].str = str;
	cur[1].next = dump->list->next->next;
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
	cur = get(1);
	cur->op = typ_list;
	cur->list = 0;
	cur->next = dump4;
	dump4 = cur;
	cur = get(1);
	cur->op = typ_list;
	cur->list = 0;
	cur->next = dump5;
	dump5 = cur;
	while (dump1->list) {
	    cur = get(1);
	    cur->op = dump1->list->op;
	    cur->val = dump1->list->val;
	    cur->next = dump->list->next->next;
	    stack = cur;
	    exeterm(dump->list->list);
	    cur = get(1);
	    cur->op = dump1->list->op;
	    cur->val = dump1->list->val;
	    cur->next = 0;
	    if (stack->num)
		if (!dump2->list)
		    dump3->list = dump2->list = cur;
		else
		    dump3->list = dump3->list->next = cur;
	    else if (!dump4->list)
		dump5->list = dump4->list = cur;
	    else
		dump5->list = dump5->list->next = cur;
	    dump1->list = dump1->list->next;
	}
	cur = get(2);
	cur->op = typ_list;
	cur->list = dump4->list;		// false
	cur->next = &cur[1];
	cur[1].op = typ_list;
	cur[1].list = dump2->list;		// true
	cur[1].next = dump->list->next->next;
	stack = cur;
	dump5 = dump5->next;
	dump4 = dump4->next;
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
