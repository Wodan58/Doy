/*
    module  : do_rand.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "ident.h"

/*
rand  :  ->  I
I is a random integer.
*/
void do_rand()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = rand();
    cur->next = stack;
    stack = cur;
}
