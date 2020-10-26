/*
    module  : do_mod.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
mod  :  I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
void do_mod()
{
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && (stack->op == typ_integer ||
	   stack->op == typ_float));
    cur = get(1);
    node = stack->next;
    switch (stack->op) {
    case typ_float :
	assert(stack->dbl != 0.0);
	switch (node->op) {
	case typ_float :
	    cur->dbl = fmod(node->dbl, stack->dbl);
	    break;

	default :
	    cur->dbl = fmod((double)node->num, stack->dbl);
	    break;
	}
	cur->op = typ_float;
	break;

    default :
	assert(stack->num != 0);
	switch (node->op) {
	case typ_float :
	    cur->dbl = fmod(node->dbl, (double)stack->num);
	    break;

	default :
	    cur->num = node->num % stack->num;
	    break;
	}
	cur->op = node->op;
	break;
    }
    cur->next = node->next;
    stack = cur;
}
