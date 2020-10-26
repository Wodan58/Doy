/*
    module  : do_i.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
i  :  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
void do_i()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next;
    exeterm(dump->list->list);
    dump = dump->next;
}
