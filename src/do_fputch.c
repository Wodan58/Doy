/*
    module  : do_fputch.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fputch  :  S C  ->  S
The character C is written to the current position of stream S.
*/
void do_fputch()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_integer &&
	   stack->next->op == typ_file && stack->next->fp);
    fputc(stack->num, stack->next->fp);
    stack = stack->next;
}
