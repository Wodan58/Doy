/*
    module  : do_cons.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "defs.h"
#include "data.h"
#include "ident.h"
#include "set32.h"
#include "local.h"

/*
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_cons()
{
    int i, j;
    char *str;
    data_t *cur = 0;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	stack = stack->next;
	i = stack->num;
	assert((stack->op == typ_char || stack->op == typ_integer) && i >= 0 &&
		i < SETSIZE);
	cur = get(1);
	cur->op = typ_set;
	cur->num = set_bit(j, i);
	break;

    case typ_string :
	assert(stack->str);
	str = malloc(strlen(stack->str) + 2);
	strcpy(str + 1, stack->str);
	stack = stack->next;
	assert(stack->op == typ_char);
	*str = stack->num;
	cur = get(1);
	cur->op = typ_string;
	cur->str = str;
	break;

    case typ_list :
#ifdef NOTHING_INSTEAD_OF_ERROR
	if (stack->next->op == typ_symbol && stack->next->num == sym_nothing) {
	    cur = get(1);
	    cur->op = typ_list;
	    cur->list = stack->list;
	    stack = stack->next;
	} else {
#endif
	    cur = get(2);
	    cur->op = typ_list;
	    cur->list = &cur[1];
	    cur[1].next = stack->list;
	    stack = stack->next;
	    cur[1].op = stack->op;
	    cur[1].val = stack->val;
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
