/*
    module  : do_false.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "boole.h"

/*
false  :  ->  false
Pushes the value false.
*/
void do_false()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = FALSE;
    cur->next = stack;
    stack = cur;
}
