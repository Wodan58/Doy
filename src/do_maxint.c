/*
    module  : do_maxint.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "set32.h"

/*
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
void do_maxint()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = MAXINT;
    cur->next = stack;
    stack = cur;
}
