/*
    module  : do_rest.c
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

/*
rest  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void do_rest()
{
    int i, j;
    char *str;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	assert(j);
	for (i = 0; !tst_bit(j, i); i++)
	    ;
	cur = get(1);
	cur->op = typ_set;
	cur->num = del_bit(j, i);
	cur->next = stack->next;
	stack = cur;
	break;

    case typ_string :
	str = stack->str;
	assert(str && *str);
	cur = get(1);
	cur->op = typ_string;
	cur->str = strdup(str + 1);
	cur->next = stack->next;
	stack = cur;
	break;

    case typ_list :
#ifndef NOTHING_INSTEAD_OF_ERROR
	assert(stack->list);
#endif
	if (stack->list) {
	    cur = get(1);
	    cur->op = typ_list;
	    cur->list = stack->list->next;
	    cur->next = stack->next;
	    stack = cur;
	}
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
}
