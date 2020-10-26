/*
    module  : do_fremove.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
void do_fremove()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_string);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = !remove(stack->str);
    cur->next = stack->next;
    stack = cur;
}
