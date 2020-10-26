/*
    module  : do_ord.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
ord  :  C  ->  I
Integer I is the Ascii value of character C (or logical or integer).
*/
void do_ord()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    cur = get(1);
    cur->op = typ_integer;
    cur->num = stack->num;
    cur->next = stack->next;
    stack = cur;
}
