/*
    module  : do_integer.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
integer  :  X  ->  B
Tests whether X is an integer.
*/
void do_integer()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->op == typ_integer;
    cur->next = stack->next;
    stack = cur;
}
