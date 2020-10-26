/*
    module  : do_body.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "symbol.h"
#include "local.h"

/*
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
void do_body()
{
    long num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_symbol);
    if (stack->op == typ_symbol && stack->num < userindex) {
	num = joy_table[stack->num].value;
	if (user(num)) {
	    cur = get(1);
	    cur->op = typ_list;
	    cur->list = (data_t *)num;
	    cur->next = stack->next;
	    stack = cur;
	}
    }
}
