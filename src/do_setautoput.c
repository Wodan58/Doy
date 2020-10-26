/*
    module  : do_setautoput.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
setautoput  :  I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
void do_setautoput()
{
    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    autoput = stack->num;
    stack = stack->next;
}
