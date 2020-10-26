/*
    module  : do_take.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "set32.h"

/*
take  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
void do_take()
{
    char *str;
    int i, j, num;
    data_t *cur = 0, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    num = stack->num;
    stack = stack->next;
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	for (i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i))
		if (num-- == 0)
		    break;
	cur = get(1);
	cur->op = typ_set;
	cur->num = set_take(j, i);
	break;

    case typ_string :
	str = malloc(num + 1);
	strncpy(str, stack->str, num);
	str[num] = 0;
	cur = get(1);
	cur->op = typ_string;
	cur->str = str;
	break;

    case typ_list :
	cur = get(num + 1);
	cur->op = typ_list;
	cur->list = &cur[i = 1];
	for (node = stack->list; i <= num && node; i++, node = node->next) {
	    cur[i].op = node->op;
	    cur[i].val = node->val;
	    cur[i].next = &cur[i + 1];
	}
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = stack->next;
    stack = cur;
}
