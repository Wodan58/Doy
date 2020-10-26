/*
    module  : do_abs.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
abs  :  N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1,
or float N2 is the absolute value (0.0 ..) of float N1.
*/
void do_abs()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_integer || stack->op == typ_float));
    switch (stack->op) {
    case typ_float :
	if (stack->dbl < 0.0) {
	    cur = get(1);
	    cur->op = typ_float;
	    cur->dbl = -stack->dbl;
	    cur->next = stack->next;
	    stack = cur;
	}
	break;

    default :
	if (stack->num < 0) {
	    cur = get(1);
	    cur->op = typ_integer;
	    cur->num = -stack->num;
	    cur->next = stack->next;
	    stack = cur;
	}
	break;
    }
}
