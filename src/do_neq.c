/*
    module  : do_neq.c
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
!=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
static int neq(data_t *node, data_t *temp)
{
    int i, num = 0;
    char *str, *buf;

    switch (node->op) {
    case typ_logical :
    case typ_char :
    case typ_integer :
	switch (temp->op) {
	case typ_float :
	    num = node->num != temp->dbl;
	    break;

	default :
	    num = node->num != temp->num;
	    break;
	}
	break;

    case typ_float :
	switch (temp->op) {
	case typ_float :
	    num = node->dbl != temp->dbl;
	    break;

	default :
	    num = node->dbl != temp->num;
	    break;
	}
	break;

    default :
	num = node->val != temp->val;
	break;

    case typ_string :
    case typ_symbol :
	switch (temp->op) {
	case typ_symbol :
	case typ_string :
	    if ((i = node->num) < userindex)
		str = joy_table[i].name;
	    else
		str = node->str;
	    if ((i = temp->num) < userindex)
		buf = joy_table[i].name;
	    else
		buf = temp->str;
	    num = strcmp(str, buf) != 0;
	    break;
	}
	break;
    }
    return num;
}

void do_neq()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = neq(stack->next, stack);
    cur->next = stack->next->next;
    stack = cur;
}
