/*
    module  : do_list.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
list  :  X  ->  B
Tests whether X is a list.
*/
void do_list()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->op == typ_list;
    cur->next = stack->next;
    stack = cur;
}
