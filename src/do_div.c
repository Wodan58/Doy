/*
    module  : do_div.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
div  :  I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
void do_div()
{
    div_t qr;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_integer &&
	   stack->next->op == typ_integer && stack->num);
    qr = div(stack->next->num, stack->num);
    cur = get(2);
    cur->op = typ_integer;
    cur->num = qr.rem;
    cur->next = &cur[1];
    cur[1].op = typ_integer;
    cur[1].num = qr.quot;
    cur[1].next = stack->next;
    stack = cur;
}
