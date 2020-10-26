/*
    module  : is_set.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 set type  :  ->  {...}
The type of sets of small non-negative integers.
The maximum is platform dependent, typically the range is 0..31.
Literals are written inside curly braces.
Examples:  {}  {0}  {1 3 5}  {19 18 17}.
*/
void is_set(int num)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_set;
    cur->num = num;
    cur->next = stack;
    stack = cur;
}
