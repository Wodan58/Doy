/*
    module  : do_settracegc.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
__settracegc  :  I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
void do_settracegc()
{
    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    tracegc = stack->num;
    stack = stack->next;
}
