/*
    module  : do_putchars.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "print.h"

/*
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
void do_putchars()
{
    char *str;
    data_t cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_string);
    if ((str = stack->str) == 0)
	str = "(null)";
    cur.op = typ_symbol;
    cur.str = str;
    printfactor(&cur, stdout);
    stack = stack->next;
}
