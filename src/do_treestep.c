/*
    module  : do_treestep.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

static void do_data()
{
    data_t *cur;

    cur = get(1);
    cur->op = pop();
    cur->val = pop();
    cur->next = stack;
    stack = cur;
}

static void save(data_t *cur)
{
    put((long)do_data);
    put(-cur->op);
    put(cur->val);
    put(-1);
}

/*
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
static void treestep(data_t *root)
{
    data_t *prev, *cur, *next;

    if (!root)
	return;
    prev = (data_t *)-1;
    cur = root;
    for (;;) {
	cur->op = -cur->op;
	if (abs(cur->op) != typ_list) {
	    if (cur->op < 0)
		save(cur);
	    next = cur->next;
	} else {
	    next = cur->list;
	    cur->list = cur->next;
	}
	cur->next = prev;
	prev = cur;
	if ((cur = next) == (data_t *)-1)
	    break;
	if (cur)
	    continue;
	cur = prev;
	prev = 0;
    }
}

/*
    De werkwijze is als volgt: stap door de tree en alloceer de nodes op de
    dump. Reverse de dump. Zet een voor een de nodes van de dump op de stack
    en voer loop(pos) uit. In plaats daarvan kan op, val en do_data ook in de
    code gealloceerd worden. De werkwijze is dan het achtereenvolgens uitvoeren
    van de nieuwe code en de subroutine die op pos is opgeslagen.
*/
void do_treestep()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = stack;
    cur->next = dump;
    dump = cur;
    stack = stack->next;
    num = used();
    treestep(stack->list);
    rev(num, used() - 1);
    stack = stack->next;
    while (num < used()) {
	loop();
	exeterm(dump->list->list);
    }
    dump = dump->next;
}
