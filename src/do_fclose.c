/*
    module  : do_fclose.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
void do_fclose()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    if (stack->fp)
	fclose(stack->fp);
    stack = stack->next;
}
