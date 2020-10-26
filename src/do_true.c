/*
    module  : do_true.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "boole.h"

/*
true  :  ->  true
Pushes the value true.
*/
void do_true()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = TRUE;
    cur->next = stack;
    stack = cur;
}
