/*
    module  : do_file.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
file  :  F  ->  B
Tests whether F is a file.
*/
void do_file()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->op == typ_file;
    cur->next = stack->next;
    stack = cur;
}
