/*
    module  : do_echo.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "input.h"

/*
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
void do_echo()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = echoflag;
    cur->next = stack;
    stack = cur;
}
