/*
    module  : do_frename.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
frename  :  P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
void do_frename()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_string &&
	   stack->next->op == typ_string);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = !rename(stack->next->str, stack->str);
    cur->next = stack->next->next;
    stack = cur;
}
