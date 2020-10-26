/*
    module  : is_logical.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 truth value type  :  ->  B
The logical type, or the type of truth values.
It has just two literals: true and false.
*/
void is_logical(int num)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = num;
    cur->next = stack;
    stack = cur;
}
