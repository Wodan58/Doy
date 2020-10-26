/*
    module  : do_autoput.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
void do_autoput()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = autoput;
    cur->next = stack;
    stack = cur;
}
