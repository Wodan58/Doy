/*
    module  : do_size.c
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
size  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
void do_size()
{
    data_t *cur;
    int i, j, num = 0;

    DEBUG(__FUNCTION__);
    assert(stack);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	for (i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i))
		num++;
	break;

    case typ_string :
	num = strlen(stack->str);
	break;

    case typ_list :
	for (cur = stack->list; cur; cur = cur->next)
	    num++;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur = get(1);
    cur->op = typ_integer;
    cur->num = num;
    cur->next = stack->next;
    stack = cur;
}
