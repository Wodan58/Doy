/*
    module  : do_swons.c
    version : 1.3
    date    : 02/22/21
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
swons  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_swons()
{
    int i, j;
    char *str;
    data_t *cur = 0;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    switch (stack->next->op) {
    case typ_set :
	j = stack->num;
	assert((stack->op == typ_char || stack->op == typ_integer) && j >= 0 &&
	       j < SETSIZE);
	stack = stack->next;
	i = stack->num;
	cur = get(1);
	cur->op = typ_set;
	cur->num = set_bit(i, j);
	break;

    case typ_string :
	assert(stack->op == typ_char);
	i = stack->num;
	stack = stack->next;
	assert(stack->str);
	str = malloc(strlen(stack->str) + 2);
	strcpy(str + 1, stack->str);
	*str = i;
	cur = get(1);
	cur->op = typ_string;
	cur->str = str;
	break;

    case typ_list :
#ifdef NOTHING_INSTEAD_OF_ERROR
	if (stack->op == typ_symbol && stack->num == sym_nothing) {
	    stack = stack->next;
	    return;
	} else {
#endif
	    cur = get(2);
	    cur->op = typ_list;
	    cur->list = &cur[1];
	    cur[1].op = stack->op;
	    cur[1].val = stack->val;
	    stack = stack->next;
	    cur[1].next = stack->list;
#ifdef NOTHING_INSTEAD_OF_ERROR
	}
#endif
	break;

    default :
	assert(stack->next->op == typ_set || stack->next->op == typ_string ||
	       stack->next->op == typ_list);
	return;
    }
    cur->next = stack->next;
    stack = cur;
}
