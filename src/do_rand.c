/*
    module  : do_rand.c
    version : 1.3
    date    : 02/22/21
*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "ident.h"

int my_rand(void);

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
    cur->num = my_rand();
    cur->next = stack;
    stack = cur;
}
