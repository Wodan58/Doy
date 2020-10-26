/*
    module  : do_intern.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "lookup.h"

/*
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
void do_intern()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_string && stack->str);
    cur = get(1);
    cur->op = typ_symbol;
    cur->num = lookup1(stack->str);
    cur->next = stack->next;
    stack = cur;
}
