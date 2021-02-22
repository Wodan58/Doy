/*
    module  : do_srand.c
    version : 1.3
    date    : 02/22/21
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

void my_srand(unsigned num);

/*
srand  :  I  ->
Sets the random integer seed to integer I.
*/
void do_srand()
{
    DEBUG(__FUNCTION__);
    assert(stack->op == typ_integer);
    my_srand(stack->num);
    stack = stack->next;
}
