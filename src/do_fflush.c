/*
    module  : do_fflush.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
void do_fflush()
{
    DEBUG(__FUNCTION__);
    assert(stack->op == typ_file && stack->fp);
    fflush(stack->fp);
}
