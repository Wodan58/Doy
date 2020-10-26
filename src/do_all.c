/*
    module  : do_all.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "boole.h"
#include "set32.h"

/*
all  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void do_all()
{
    char *str;
    data_t *cur, *node;
    int i, j, num = TRUE;

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
	for (j = stack->num, i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i)) {
		cur = get(1);
		cur->op = typ_integer;
		cur->num = i;
		cur->next = dump->list->next->next;
		stack = cur;
		exeterm(dump->list->list);
		if (!stack->num) {
		    num = FALSE;
		    break;
		}
	    }
	break;

    case typ_string :
	for (str = stack->str; *str; str++) {
	    cur = get(1);
	    cur->op = typ_char;
	    cur->num = *str;
	    cur->next = dump->list->next->next;
	    stack = cur;
	    exeterm(dump->list->list);
	    if (!stack->num) {
		num = FALSE;
		break;
	    }
	}
	break;

    case typ_list :
	for (node = stack->list; node; node = node->next) {
	    cur = get(1);
	    cur->op = node->op;
	    cur->val = node->val;
	    cur->next = dump->list->next->next;
	    stack = cur;
	    exeterm(dump->list->list);
	    if (!stack->num) {
		num = FALSE;
		break;
	    }
	}
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur = get(1);
    cur->op = typ_logical;
    cur->num = num;
    cur->next = dump->list->next->next;
    stack = cur;
    dump = dump->next;
}
