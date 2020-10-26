/*
    module  : do_compare.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "symbol.h"
#include "local.h"

/*
compare  :  A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <=, =, >=.
*/
void do_compare()
{
    char *str, *ptr;
    int i, j, num = 0;
    data_t *cur, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op != typ_list &&
	   stack->next->op != typ_list);
    node = stack->next;
    switch (node->op) {
    case typ_logical :
    case typ_char :
    case typ_integer :
	switch (stack->op) {
	case typ_logical :
	case typ_char :
	case typ_integer :
	    num = node->num - stack->num;
	    break;

	case typ_float :
	    if (node->num - stack->dbl < 0)
		num = -1;
	    else if (node->num - stack->dbl > 0)
		num = 1;
	    break;

	default :
	    assert(node->op == typ_logical || node->op == typ_char ||
		   node->op == typ_integer || node->op == typ_float);
	}
	break;

    case typ_float :
	switch (stack->op) {
	case typ_float :
	    if (node->dbl - stack->dbl < 0)
		num = -1;
	    else if (node->dbl - stack->dbl > 0)
		num = 1;
	    break;

	case typ_logical :
	case typ_char :
	case typ_integer :
	    if (node->dbl - stack->num < 0)
		num = -1;
	    else if (node->dbl - stack->num > 0)
		num = 1;
	    break;

	default :
	    assert(node->op == typ_logical || node->op == typ_char ||
		   node->op == typ_integer || node->op == typ_float);
	}
	break;

    case typ_set :
	i = node->num;
	j = stack->num;
	if (i == j)
	    num = 0;
	else if (!(i & ~j))
	    num = -1;
	else if (!(j & ~i))
	    num = 1;
	else
	    num = 2;
	goto einde;

    default :
	num = node->val - stack->val;
	break;

    case typ_string :
    case typ_symbol :
	switch (stack->op) {
	case typ_string :
	case typ_symbol :
	    if ((i = node->num) < userindex)
		str = joy_table[i].name;
	    else
		str = node->str;
	    if ((i = stack->num) < userindex)
		ptr = joy_table[i].name;
	    else
		ptr = stack->str;
	    num = strcmp(str, ptr);
	    break;
	}
	break;
    }
    if (num < 0)
	num = -1;
    else if (num > 0)
	num = 1;
einde:
    cur = get(1);
    cur->op = typ_integer;
    cur->num = num;
    cur->next = node->next;
    stack = cur;
}
