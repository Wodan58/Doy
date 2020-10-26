/*
    module  : do_nothing.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
nothing  :  ->  nothing
Pushing the value nothing.
*/
void do_nothing()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_symbol;
    cur->num = sym_nothing;
    cur->next = stack;
    stack = cur;
}
