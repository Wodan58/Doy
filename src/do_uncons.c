/*
    module  : do_uncons.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "defs.h"
#include "data.h"
#include "ident.h"
#include "set32.h"
#include "local.h"

/*
uncons  :  A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void do_uncons()
{
    char *str;
    data_t *cur;
    int i, j, num;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(2);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	assert(j);
	for (i = 0; !tst_bit(j, i); i++)
	    ;
	cur->op = typ_set;
	cur->num = del_bit(j, i);
	cur[1].op = typ_integer;
	cur[1].num = i;
	break;

    case typ_string :
	str = stack->str;
	assert(str && *str);
	num = *str++;
	cur->op = typ_string;
	cur->str = strdup(str);
	cur[1].op = typ_char;
	cur[1].num = num;
	break;

    case typ_list :
	cur->op = typ_list;
#ifdef NOTHING_INSTEAD_OF_ERROR
	if (!stack->list) {
	    cur->list = 0;
	    cur[1].op = typ_symbol;
	    cur[1].num = sym_nothing;
	} else {
#else
	    assert(stack->list);
#endif
	    cur->list = stack->list->next;
	    cur[1].op = stack->list->op;
	    cur[1].val = stack->list->val;
#ifdef NOTHING_INSTEAD_OF_ERROR
	}
#endif
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = &cur[1];
    cur[1].next = stack->next;
    stack = cur;
}
