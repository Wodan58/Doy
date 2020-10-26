/*
    module  : do_system.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
system  :  "command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
void do_system()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_string && stack->str);
    system(stack->str);
    stack = stack->next;
}
