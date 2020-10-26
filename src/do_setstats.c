/*
    module  : do_setstats.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "value.h"

/*
__setstats  :  I  ->
Sets value of flag for statistics to I (= 0..1).
*/
void do_setstats()
{
    DEBUG(__FUNCTION__);
    assert(stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer);
    statistics = stack->num;
    stack = stack->next;
}
