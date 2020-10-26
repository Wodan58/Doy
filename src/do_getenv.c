/*
    module  : do_getenv.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
void do_getenv()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_string && stack->str);
    cur = get(1);
    cur->op = typ_string;
    cur->str = getenv(stack->str);
    cur->next = stack->next;
    stack = cur;
}
