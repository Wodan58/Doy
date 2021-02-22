/*
    module  : do_of.c
    version : 1.3
    date    : 02/22/21
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "set32.h"

/*
of  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
void do_of()
{
    char *str;
    int i, j, num;
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->op == typ_integer &&
	   stack->next->num >= 0);
    num = stack->next->num;
    cur = get(1);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	for (i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i))
		if (num-- == 0)
		    break;
	assert(j && i < SETSIZE);
	cur->op = typ_integer;
	cur->num = i;
	break;

    case typ_string :
	str = stack->str;
	assert(num < (int)strlen(str));
	cur->op = typ_char;
	cur->num = str[num];
	break;

    case typ_list :
	for (node = stack->list; node && num-- > 0; node = node->next)
	    ;
	assert(node && num == -1);
	if (!node)
	    return;
	cur->op = node->op;
	cur->val = node->val;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = stack->next->next;
    stack = cur;
}
