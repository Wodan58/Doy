/*
    module  : is_string.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 string type  :  ->  "..."
The type of strings of characters. Literals are written inside double quotes.
Examples: ""  "A"  "hello world" "123".
Unix style escapes are accepted.
*/
void is_string(char *str)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_string;
    cur->str = str;
    cur->next = stack;
    stack = cur;
}
