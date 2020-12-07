/*
    module  : is_float.c
    version : 1.3
    date    : 11/23/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 float type  :  ->  F
The type of floating-point numbers.
Literals of this type are written with embedded decimal points (like 1.2)
and optional exponent specifiers (like 1.5E2)
*/
void is_float(long num)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_float;
    cur->num = num;
    cur->next = stack;
    stack = cur;
}
