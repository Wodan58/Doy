/*
    module  : do_undeferror.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
void do_undeferror()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = undeferror;
    cur->next = stack;
    stack = cur;
}
