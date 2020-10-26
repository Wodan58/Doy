/*
    module  : do_treerec.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "lookup.h"

void do_cons(void);

static int ptr = 0;

/*
treerec  :  T [[O] C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
static void aux_treerec()
{
    data_t *cur;

    put(-1);
    if (stack->next->op != typ_list) {
	proc(stack->list->list);
	stack = stack->next;
    } else {
	proc(stack->list->next);
	cur = get(2);
	cur->op = typ_list;
	cur->list = &cur[1];
	cur->next = stack;
	cur[1].op = typ_symbol;
	cur[1].num = ptr;
	cur[1].next = 0;
	stack = cur;
	do_cons();
    }
}

/*
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[O] [C] treerec] C.
*/
void do_treerec()
{
    int num;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->op == typ_list
	   && stack->next->op == typ_list);
    do_cons();
    if (!ptr)
	ptr = lookup1("_treerec");
    num = used();
    aux_treerec();
    while (num < used())
	loop();
}
