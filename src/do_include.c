/*
    module  : do_include.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "input.h"

/*
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
void do_include()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_string && stack->str);
    newfile(stack->str);
    stack = stack->next;
}
