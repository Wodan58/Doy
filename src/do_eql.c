/*
    module  : do_eql.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "dolib.h"

void do_eql()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = eql(stack->next, stack);
    cur->next = stack->next->next;
    stack = cur;
}
