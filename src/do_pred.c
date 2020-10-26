/*
    module  : do_pred.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
pred  :  M  ->  N
Numeric N is the predecessor of numeric M.
*/
void do_pred()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    cur = get(1);
    cur->op = stack->op;
    cur->num = stack->num - 1;
    cur->next = stack->next;
    stack = cur;
}
