/*
    module  : do_fopen.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
void do_fopen()
{
    char *mode;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_string &&
	   stack->next->op == typ_string);
    mode = stack->str;
    stack = stack->next;
    cur = get(1);
    cur->op = typ_file;
    cur->fp = fopen(stack->str, mode);
    cur->next = stack->next;
    stack = cur;
}
