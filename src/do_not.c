/*
    module  : do_not.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
not  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
void do_not()
{
    int op;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    switch (op = stack->op) {
    case typ_set :
	cur->num = ~stack->num;
	break;

    case typ_string :
	cur->num = !*stack->str;
	break;

    case typ_logical :
    case typ_char :
    case typ_integer :
	cur->num = !stack->num;
	break;

    case typ_list :
	cur->num = !stack->list;
	break;

    case typ_float :
	cur->num = !stack->dbl;
	break;

    case typ_file :
	cur->num = !stack->fp;
	break;

    default :
	assert(op == typ_set || op == typ_string || op == typ_logical ||
	       op == typ_char || op == typ_integer || op == typ_list ||
	       op == typ_float || op == typ_file);
	break;
    }
    cur->op = op == typ_set ? op : typ_logical;
    cur->next = stack->next;
    stack = cur;
}
