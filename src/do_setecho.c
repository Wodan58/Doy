/*
    module  : do_setecho.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "input.h"
#include "listing.h"

/*
setecho  :  I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
void do_setecho()
{
    int rv;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    rv = echoflag;
    echoflag = stack->num;
    if (!rv && echoflag)
	openlisting();
    stack = stack->next;
}
