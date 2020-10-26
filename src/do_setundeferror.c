/*
    module  : 
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
setundeferror  :  I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
void do_setundeferror()
{
    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    undeferror = stack->num;
    stack = stack->next;
}
