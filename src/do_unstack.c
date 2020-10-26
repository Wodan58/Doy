/*
    module  : do_unstack.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
void do_unstack()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list);
    stack = stack->list;
}
