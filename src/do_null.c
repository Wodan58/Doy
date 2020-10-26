/*
    module  : do_null.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
null  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void do_null()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    switch (stack->op) {
    case typ_string :
	assert(stack->str);
	cur->num = !*stack->str;
	break;

    case typ_list :
	cur->num = !stack->list;
	break;

    case typ_float :
	cur->num = !stack->dbl;
	break;

    case typ_file :
	cur->num = !cur->fp;
	break;

    default :
	cur->num = !stack->num;
	break;
    }
    cur->next = stack->next;
    stack = cur;
}
