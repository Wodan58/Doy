/*
    module  : do_neg.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
neg  :  I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
void do_neg()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_integer || stack->op == typ_float));
    switch (stack->op) {
    case typ_float :
	if (stack->dbl) {
	    cur = get(1);
	    cur->op = typ_float;
	    cur->dbl = -stack->dbl;
	    cur->next = stack->next;
	    stack = cur;
	}
	break;

    default :
	if (stack->num) {
	    cur = get(1);
	    cur->op = typ_integer;
	    cur->num = -stack->num;
	    cur->next = stack->next;
	    stack = cur;
	}
	break;
    }
}
