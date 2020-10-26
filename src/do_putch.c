/*
    module  : do_putch.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "print.h"

/*
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
void do_putch()
{
    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    putch(stack->num, stdout);
    stack = stack->next;
}
