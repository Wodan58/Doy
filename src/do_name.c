/*
    module  : do_name.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "symbol.h"
#include "local.h"

static char *names[] = {
    0,
    " symbol type",
    " truth value type",
    " character type",
    " integer type",
    " set type",
    " string type",
    " list type",
    " float type",
    " file type"
};

/*
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
void do_name()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack);
    cur = get(1);
    cur->op = typ_string;
    if (stack->op == typ_symbol)
	if ((num = stack->num) < userindex)
	    cur->str = joy_table[num].name;
	else
	    cur->str = stack->str;
    else
	cur->str = names[stack->op];
    cur->next = stack->next;
    stack = cur;
}
