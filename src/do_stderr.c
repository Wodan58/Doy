/*
    module  : do_stderr.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
stderr  :  ->  S
Pushes the standard error stream.
*/
void do_stderr()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_file;
    cur->fp = stderr;
    cur->next = stack;
    stack = cur;
}
