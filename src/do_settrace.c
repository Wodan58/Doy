/*
    module  : do_settrace.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "value.h"

/*
__settrace  :  I  ->
Sets value of flag for tracing execution to I (= 0..1).
*/
void do_settrace()
{
    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    trace = stack->num;
    stack = stack->next;
}
