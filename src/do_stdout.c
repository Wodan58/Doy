/*
    module  : do_stdout.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
stdout  :  ->  S
Pushes the standard output stream.
*/
void do_stdout()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_file;
    cur->fp = stdout;
    cur->next = stack;
    stack = cur;
}
