/*
    module  : do_time.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "ident.h"

/*
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
void do_time()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = time(0);
    cur->next = stack;
    stack = cur;
}
