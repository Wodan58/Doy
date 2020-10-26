/*
    module  : do_srand.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
srand  :  I  ->
Sets the random integer seed to integer I.
*/
void do_srand()
{
    DEBUG(__FUNCTION__);
    assert(stack->op == typ_integer);
    srand(stack->num);
    stack = stack->next;
}
