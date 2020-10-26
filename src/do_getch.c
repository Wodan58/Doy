/*
    module  : do_getch.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
void do_getch()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_char;
    cur->num = getchar();
    cur->next = stack;
    stack = cur;
}
