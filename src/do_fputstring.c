/*
    module  : do_fputstring.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "print.h"

/*
fputstring  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
== fputchars, as a temporary alternative.
*/
void do_fputstring()
{
    data_t cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_string && stack->str &&
	   stack->next->op == typ_file && stack->next->fp);
    cur.op = typ_symbol;
    cur.str = stack->str;
    stack = stack->next;
    printfactor(&cur, stack->fp);
}
