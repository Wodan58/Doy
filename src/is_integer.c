/*
    module  : is_integer.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 integer type  :  ->  I
The type of negative, zero or positive integers.
Literals are written in decimal notation. Examples:  -123   0   42.
*/
void is_integer(int num)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = num;
    cur->next = stack;
    stack = cur;
}
