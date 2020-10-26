/*
    module  : do_clock.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "ident.h"
#include "stats.h"

/*
clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
void do_clock()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = clock() - stat_start;
    cur->next = stack;
    stack = cur;
}
