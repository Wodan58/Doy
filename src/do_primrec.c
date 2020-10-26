/*
    module  : do_primrec.c
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
primrec  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void do_primrec()
{
    char *str;
    int i, j, num = 0;
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->op == typ_list
	   && stack->next->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    node = stack->next->next;
    stack = node->next;
    switch (node->op) {
    case typ_set :
	for (j = node->num, i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i)) {
		cur = get(1);
		cur->op = typ_integer;
		cur->num = i;
		cur->next = stack;
		stack = cur;
		num++;
	    }
	break;

    case typ_string :
	for (str = node->str; *str; str++) {
	    cur = get(1);
	    cur->op = typ_char;
	    cur->num = *str;
	    cur->next = stack;
	    stack = cur;
	    num++;
	}
	break;

    case typ_list :
	cur = get(1);
	cur->op = typ_list;
	cur->list = node->list;
	cur->next = dump1;
	dump1 = cur;
	while (dump1->list) {
	    cur = get(1);
	    cur->op = dump1->list->op;
	    cur->val = dump1->list->val;
	    cur->next = stack;
	    stack = cur;
	    num++;
	    dump1->list = dump1->list->next;
	}
	dump1 = dump1->next;
	break;

    case typ_integer :
	for (num = i = stack->num; i > 0; i--) {
	    cur = get(1);
	    cur->op = typ_integer;
	    cur->num = i;
	    cur->next = stack;
	    stack = cur;
	}
	break;

    default :
	assert(node->op == typ_set || node->op == typ_string ||
	       node->op == typ_list);
	break;
    }
    exeterm(dump->list->next->list);
    while (num--)
	exeterm(dump->list->list);
    dump = dump->next;
}
