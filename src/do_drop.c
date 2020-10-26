/*
    module  : do_drop.c
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
drop  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
void do_drop()
{
    char *str;
    int i, j, num;
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    num = stack->num;
    stack = stack->next;
    cur = get(1);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	for (i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i))
		if (num-- == 0)
		    break;
	cur->op = typ_set;
	cur->num = set_drop(j, i);
	break;

    case typ_string :
	for (str = stack->str; *str && num-- > 0; str++)
	    ;
	cur->op = typ_string;
	cur->str = strdup(str);
	break;

    case typ_list :
	for (node = stack->list; node && num-- > 0; node = node->next)
	    ;
	cur->op = typ_list;
	cur->list = node;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = stack->next;
    stack = cur;
}
