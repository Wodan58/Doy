/*
    module  : do_setlisting.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "value.h"
#include "listing.h"

/*
__setlisting  :  I  ->
Sets value of flag for listing to I (0..9).
*/
void do_setlisting()
{
    int rv;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    rv = writelisting;
    writelisting = stack->num;
    if (!rv && writelisting)
	openlisting();
    stack = stack->next;
}
