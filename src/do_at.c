/*
    module  : do_at.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "set32.h"

/*
at  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void do_at()
{
    char *str;
    int i, j, num;
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_integer);
    num = stack->num;
    assert(num >= 0);
    stack = stack->next;
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
	cur->op = node->op;
	cur->val = node->val;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = stack->next;
    stack = cur;
}
