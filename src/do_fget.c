/*
    module  : do_fget.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "token.h"
#include "input.h"
#include "factor.h"

/*
fget  :  S  ->  S  F
Reads a factor from stream S and pushes it onto stack.
*/
void do_fget()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_file && stack->fp);
    redirect(stack->fp);
    getsym();
    readfactor();
}
