/*
    module  : do_stdin.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
stdin  :  ->  S
Pushes the standard input stream.
*/
void do_stdin()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_file;
    cur->fp = stdin;
    cur->next = stack;
    stack = cur;
}
