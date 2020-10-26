/*
    module  : do_string.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
string  :  X  ->  B
Tests whether X is a string.
*/
void do_string()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->op == typ_string;
    cur->next = stack->next;
    stack = cur;
}
