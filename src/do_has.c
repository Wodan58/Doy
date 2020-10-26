/*
    module  : do_has.c
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
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
void do_has()
{
    int i, j;
    data_t *cur, *node, *temp;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = typ_logical;
    node = stack->next;
    switch (node->op) {
    case typ_set :
	i = node->num;
	j = stack->num;
	cur->num = tst_bit(i, j) != 0;
	break;

    case typ_string :
	cur->num = strchr(node->str, stack->num) != 0;
	break;

    case typ_list :
	for (temp = node->list; temp && !eql(temp, stack); temp = temp->next)
	    ;
	cur->num = temp != 0;
	break;

    default :
	assert(node->op == typ_set || node->op == typ_string ||
	       node->op == typ_list);
	break;
    }
    cur->next = node->next;
    stack = cur;
}
