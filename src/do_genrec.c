/*
    module  : do_genrec.c
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
genrec  :  [[B] [T] [R1] R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[B] [T] [R1] [R2] genrec] R2.
*/
static void aux_genrec()
{
    int num;
    data_t *cur;

    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next;
    exeterm(dump->list->list->list);
    num = stack->num;
    stack = dump->list->next;
    if (num)
	exeterm(dump->list->list->next->list);
    else {
	exeterm(dump->list->list->next->next->list);
	cur = get(3);
	cur->op = typ_list;
	cur->list = &cur[1];
	cur->next = &cur[2];
	cur[1].op = typ_symbol;
	cur[1].num = ptr;
	cur[1].next = 0;
	cur[2].op = typ_list;
	cur[2].list = dump->list->list;
	cur[2].next = stack;
	stack = cur;
	do_cons();
	put(-1);
	proc(dump->list->list->next->next->next);
    }
    dump = dump->next;
}

/*
genrec  :  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[B] [T] [R1] [R2] genrec] R2.
*/
void do_genrec()
{
    int num;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next && stack->next->next->next
	   && stack->op == typ_list && stack->next->op == typ_list &&
	   stack->next->next->op == typ_list &&
	   stack->next->next->next->op == typ_list);
    do_cons();
    do_cons();
    do_cons();
    if (!ptr)
        ptr = lookup1("_genrec");
    num = used();
    aux_genrec();
    while (num < used())
	loop();
}
