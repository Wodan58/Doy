/*
    module  : do_equal.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "boole.h"
#include "dolib.h"

/*
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
static int equal(data_t *node, data_t *temp)
{
    if (node == temp)
	return TRUE;
    if (!node || !temp)
	return FALSE;
    if (node->op != temp->op)
	return FALSE;
    if (node->op != typ_list)
	return eql(node, temp);
    node = node->list;
    temp = temp->list;
    while (node && temp) {
	if (!equal(node, temp))
	    return FALSE;
	node = node->next;
	temp = temp->next;
    }
    return node == temp;
}

void do_equal()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = equal(stack->next, stack);
    cur->next = stack->next->next;
    stack = cur;
}
