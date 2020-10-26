/*
    module  : do_max.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
max  :  N1 N2  ->  N
N is the maximum of numeric values N1 and N2.  Also supports float.
*/
void do_max()
{
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    node = stack->next;
    switch (stack->op) {
    case typ_float :
	switch (node->op) {
	case typ_float :
	    cur->dbl = node->dbl < stack->dbl ? stack->dbl : node->dbl;
	    break;

	default :
	    cur->dbl = node->num < stack->dbl ? stack->dbl : node->num;
	    break;
	}
	cur->op = typ_float;
	break;

    default :
	switch (node->op) {
	case typ_float :
	    cur->dbl = node->dbl < stack->num ? stack->num : node->dbl;
	    break;

	default :
	    assert(stack->op == node->op && (stack->op == typ_logical ||
		   stack->op == typ_char || stack->op == typ_integer));
	    cur->num = node->num < stack->num ? stack->num : node->num;
	    break;
	}
	cur->op = node->op;
	break;
    }
    cur->next = node->next;
    stack = cur;
}
