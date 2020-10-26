/*
    module  : do_user.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "local.h"
#include "symbol.h"

/*
user  :  X  ->  B
Tests whether X is a user-defined symbol.
*/
void do_user()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_logical;
    cur->num = stack->op == typ_symbol && stack->num < userindex &&
	       user(joy_table[stack->num].value);
    cur->next = stack->next;
    stack = cur;
}
