/*
    module  : do_xor.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
xor  :  X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
void do_xor()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == stack->next->op &&
	  (stack->op == typ_set  || stack->op == typ_logical ||
	   stack->op == typ_char || stack->op == typ_integer ||
	   stack->op == typ_list));
    cur = get(1);
    cur->op = stack->op;
    cur->num = stack->next->num ^ stack->num;
    cur->next = stack->next->next;
    stack = cur;
}
