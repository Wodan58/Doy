/*
    module  : do_first.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "defs.h"
#include "data.h"
#include "ident.h"
#include "set32.h"
#include "local.h"

/*
first  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
void do_first()
{
    int i, j;
    char *str;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	assert(j);
	for (i = 0; !tst_bit(j, i); i++)
	    ;
	cur->op = typ_integer;
	cur->num = i;
	break;

    case typ_string :
	str = stack->str;
	assert(str && *str);
	cur->op = typ_char;
	cur->num = *str;
	break;

    case typ_list :
#ifdef NOTHING_INSTEAD_OF_ERROR
	if (!stack->list) {
	    cur->op = typ_symbol;
	    cur->num = sym_nothing;
	} else {
#else
	    assert(stack->list);
#endif
	    cur->op = stack->list->op;
	    cur->val = stack->list->val;
#ifdef NOTHING_INSTEAD_OF_ERROR
	}
#endif
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = stack->next;
    stack = cur;
}
