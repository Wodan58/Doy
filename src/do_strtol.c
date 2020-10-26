/*
    module  : do_strtol.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
strtol  :  S I  ->  J
String S is converted to the integer J using base I.
If I = 0, assumes base 10,
but leading "0" means base 8 and leading "0x" means base 16.
*/
void do_strtol()
{
    int base;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_integer &&
	   stack->next->op == typ_string);
    base = stack->num;
    stack = stack->next;
    cur = get(1);
    cur->op = typ_integer;
    cur->num = strtol(stack->str, 0, base);
    cur->next = stack->next;
    stack = cur;
}
