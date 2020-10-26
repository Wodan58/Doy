/*
    module  : do_sign.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
sign  :  N1  ->  N2
Integer N2 is the sign (-1 or 0 or +1) of integer N1,
or float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.
*/
void do_sign()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_integer || stack->op == typ_float));
    switch (stack->op) {
    case typ_float :
	if (stack->dbl) {
	    cur = get(1);
	    cur->op = typ_float;
	    cur->dbl = stack->dbl < 0.0 ? -1.0 : 1.0;
	    cur->next = stack->next;
	    stack = cur;
	}
	break;

    default :
	if (stack->num < -1 || stack->num > 1) {
	    cur = get(1);
	    cur->op = typ_integer;
	    cur->num = stack->num < 0 ? -1 : 1;
	    cur->next = stack->next;
	    stack = cur;
	}
	break;
    }
}
