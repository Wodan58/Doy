/*
    module  : do_argc.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

extern int g_argc;

/*
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
void do_argc()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = g_argc;
    cur->next = stack;
    stack = cur;
}
