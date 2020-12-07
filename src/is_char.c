/*
    module  : is_char.c
    version : 1.3
    date    : 11/23/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 character type  :  ->  C
The type of characters. Literals are written with a single quote.
Examples:  'A  '7  ';  and so on. Unix style escapes are allowed.
*/
void is_char(long num)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_char;
    cur->num = num;
    cur->next = stack;
    stack = cur;
}
