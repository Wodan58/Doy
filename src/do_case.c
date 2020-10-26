/*
    module  : do_case.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "dolib.h"

/*
case  :  X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
void do_case()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list && stack->list);
    for (cur = stack->list; cur->next && !eql(cur->list, stack->next);
	 cur = cur->next)
	;
    stack = stack->next;
    if (!cur->next)
	exeterm(cur->list);
    else {
	stack = stack->next;
	exeterm(cur->list->next);
    }
}
