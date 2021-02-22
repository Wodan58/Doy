/*
    module  : do_in.c
    version : 1.3
    date    : 02/22/21
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "set32.h"
#include "dolib.h"

/*
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
void do_in()
{
    int i, j;
    data_t *cur, *temp, *node;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = typ_logical;
    temp = stack->next;
    switch (stack->op) {
    case typ_set :
	i = temp->num;
	j = stack->num;
	cur->num = tst_bit(j, i) != 0;
	break;

    case typ_string :
	cur->num = strchr(stack->str, temp->num) != 0;
	break;

    case typ_list :
	for (node = stack->list; node && !eql2(node, temp); node = node->next)
	    ;
	cur->num = node != 0;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = temp->next;
    stack = cur;
}
