/*
    module  : do_strtod.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
strtod  :  S  ->  R
String S is converted to the float R.
*/
void do_strtod()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_string && stack->str);
    cur = get(1);
    cur->op = typ_float;
    cur->dbl = atof(stack->str);
    cur->next = stack->next;
    stack = cur;
}
