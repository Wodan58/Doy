/*
    module  : aux_eql.c
    version : 1.3
    date    : 11/23/20
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "symbol.h"
#include "local.h"

/*
=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X equal to Y.  Also supports float.
*/
static int eql1(data_t *node, data_t *temp, int type)
{
    int i, num = 0;
    char *str, *ptr;

    switch (node->op) {
    case typ_logical :
    case typ_char :
    case typ_integer :
	switch (temp->op) {
	case typ_float :
	    num = node->num == temp->dbl;
	    break;

	default :
	    num = node->num == temp->num;
	    break;
	}
	break;

    case typ_float :
	switch (temp->op) {
	case typ_float :
	    num = node->dbl == temp->dbl;
	    break;

	default :
	    num = node->dbl == temp->num;
	    break;
	}
	break;

    default :
	num = node->val == temp->val;
	break;

    case typ_string :
    case typ_symbol :
	switch (temp->op) {
	case typ_string :
	case typ_symbol :
	    if ((i = node->num) >= 0 && i < userindex)
		str = joy_table[i].name;
	    else
		str = node->str;
	    if ((i = temp->num) >= 0 && i < userindex)
		ptr = joy_table[i].name;
	    else
		ptr = temp->str;
	    if (!type || node->op == temp->op)
		if (str && ptr)
		    num = strcmp(str, ptr) == 0;
	    break;
	}
	break;
    }
    return num;
}

int eql(data_t *node, data_t *temp)
{
    return eql1(node, temp, 0);
}

int eql2(data_t *node, data_t *temp)
{
    return eql1(node, temp, 1);
}
