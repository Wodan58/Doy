/*
    module  : do_in.c
    version : 1.2
    date    : 10/26/20
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
    data_t *cur, *node, *temp;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = typ_logical;
    node = stack->next;
    switch (stack->op) {
    case typ_set :
	i = node->num;
	j = stack->num;
	cur->num = tst_bit(j, i) != 0;
	break;

    case typ_string :
	cur->num = strchr(stack->str, node->num) != 0;
	break;

    case typ_list :
	for (temp = stack->list; temp && !eql2(temp, node); temp = temp->next)
	    ;
	cur->num = temp != 0;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
    cur->next = node->next;
    stack = cur;
}
