/*
    module  : do_opcase.c
    version : 1.3
    date    : 02/22/21
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "dolib.h"

/*
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void do_opcase()
{
    int op;
    data_t *cur, *node, *temp;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list && stack->list);
    cur = get(1);
    node = stack->next;
    temp = stack->list;
    if ((op = node->op) == typ_symbol)
	for ( ; temp->next && temp->op == typ_list &&
		!eql(node, temp); temp = temp->next)
	    ;
    else
	for ( ; temp->next && temp->op == typ_list &&
		temp->list->op != op; temp = temp->next)
	    ;
    assert(temp->op == typ_list);
    temp = !temp->next ? temp->list : temp->list->next;
    cur->op = typ_list;
    cur->list = temp;
    cur->next = node;
    stack = cur;
}
