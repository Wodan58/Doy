/*
    module  : do_put.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "print.h"

/*
put  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put()
{
    DEBUG(__FUNCTION__);
    if (!stack)
	return;
    assert(stack);
    if (stack->op != typ_char || !isspace(stack->num))
	newspace(stdout);
    printfactor(stack, stdout);
    stack = stack->next;
}
