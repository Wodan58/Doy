/*
    module  : do_pop.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"

/*
pop  :  X  ->
Removes X from top of the stack.
*/
void do_pop()
{
    DEBUG(__FUNCTION__);
    assert(stack);
    stack = stack->next;
}
