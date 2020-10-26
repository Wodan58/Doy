/*
    module  : do_treegenrec.c
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
treegenrec  :  T [[O1] [O2] C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
static void aux_treegenrec()
{
    data_t *cur;

    if (stack->next->op != typ_list) {
	put(-1);
	proc(stack->list->list);
	stack = stack->next;
    } else {
	cur = get(1);
	cur->op = typ_list;
	cur->list = stack;
	cur->next = dump;
	dump = cur;
	stack = stack->next;
	exeterm(dump->list->list->next->list);
	cur = get(3);
	cur->op = typ_list;
	cur->list = &cur[1];
	cur->next = &cur[2];
	cur[1].op = typ_symbol;
	cur[1].num = ptr;
	cur[1].next = 0;
	cur[2].op = dump->list->op;
	cur[2].val = dump->list->val;
	cur[2].next = stack;
	stack = cur;
	dump = dump->next;
	do_cons();
	put(-1);
	proc(stack->list->list->next->next);
    }
}

/*
treegenrec  :  T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[O1] [O2] [C] treegenrec] C.
*/
void do_treegenrec()
{
    int num;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->next->next->next
	   && stack->op == typ_list && stack->next->op == typ_list &&
	   stack->next->next->op == typ_list);
    do_cons();
    do_cons();
    if (!ptr)
	ptr = lookup1("_treegenrec");
    num = used();
    aux_treegenrec();
    while (num < used())
	loop();
}
