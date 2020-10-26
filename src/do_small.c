/*
    module  : do_small.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "set32.h"

/*
small  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
void do_small()
{
    data_t *cur;
    int i, j, num;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    switch (stack->op) {
    case typ_logical :
    case typ_integer :
	cur->num = stack->val < 2;
	break;

    case typ_set :
	j = stack->num;
	for (num = i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i))
		if (++num >= 2)
		    break;
	cur->num = num < 2;
	break;

    case typ_string :
	assert(stack->str);
	cur->num = strlen(stack->str) < 2;
	break;

    case typ_list :
	cur->num = !stack->list || !stack->list->next;
	break;

    default :
	assert(stack->op == typ_logical || stack->op == typ_integer ||
	       stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = stack->next;
    stack = cur;
}
