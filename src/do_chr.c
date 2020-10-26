/*
    module  : do_chr.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
chr  :  I  ->  C
C is the character whose Ascii value is integer I (or logical or character).
*/
void do_chr()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && (stack->op == typ_logical || stack->op == typ_char ||
	   stack->op == typ_integer));
    cur = get(1);
    cur->op = typ_char;
    cur->num = stack->num;
    cur->next = stack->next;
    stack = cur;
}
