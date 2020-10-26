/*
    module  : do_unswons.c
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
unswons  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void do_unswons()
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
	cur[1].op = typ_set;
	cur[1].num = del_bit(j, i);
	cur->op = typ_integer;
	cur->num = i;
	break;

    case typ_string :
	str = stack->str;
	assert(str && *str);
	num = *str++;
	cur[1].op = typ_string;
	cur[1].str = strdup(str);
	cur->op = typ_char;
	cur->num = num;
	break;

    case typ_list :
	cur[1].op = typ_list;
#ifdef NOTHING_INSTEAD_OF_ERROR
	if (!stack->list) {
	    cur[1].list = 0;
	    cur->op = typ_symbol;
	    cur->num = sym_nothing;
	} else {
#else
	    assert(stack->list);
#endif
	    cur[1].list = stack->list->next;
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
    cur->next = &cur[1];
    cur[1].next = stack->next;
    stack = cur;
}
