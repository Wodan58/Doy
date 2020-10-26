/*
    module  : do_builtin.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "boole.h"
#include "local.h"
#include "symbol.h"

/*
builtin  :  X  ->  B
Tests whether X is a builtin symbol.
*/
void do_builtin()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = FALSE;
    if (stack->op == typ_symbol)
	if ((num = stack->num) < userindex) {
	    num = joy_table[num].value;
	    cur->num = !user(num);
	}
    cur->next = stack->next;
    stack = cur;
}
