/*
    module  : 
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "ident.h"

/*
__memoryindex  :  ->
Pushes current value of memory.
*/
void do_memoryindex()
{
    long num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    mrep(&num, &num, &cur->num);
    cur->next = stack;
    stack = cur;
}
