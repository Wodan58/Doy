/*
    module  : do_memorymax.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "ident.h"

/*
__memorymax  : ->  I
Pushes value of total size of memory.
*/
void do_memorymax()
{
    long num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    mrep(&cur->num, &num, &num);
    cur->next = stack;
    stack = cur;
}
