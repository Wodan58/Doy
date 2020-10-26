/*
    module  : do_fput.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "chars.h"
#include "print.h"

/*
fput  :  S X  ->  S
Writes X to stream S, pops X off stack.
*/
void do_fput()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->op == typ_file &&
	   stack->next->fp);
    cur = stack->next;
    printfactor(stack, cur->fp);
    putch(SPACE, cur->fp);
    stack = cur;
}
