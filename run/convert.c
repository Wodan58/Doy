/*
    module  : convert.c
    version : 1.3
    date    : 02/22/21

    Conversion from data_t to memory_t and vice versa.
*/
#include <stdio.h>
#include "defs.h"
#include "memory.h"
#include "data.h"
#include "ident.h"
#include "factor.h"
#include "symbol.h"
#include "convert.h"

static memrange TermToMemory(data_t *cur);

static memrange kons(standardident o, long v, memrange n)
{
    memory_t node;
    symbol_t *psym;

    if (o == typ_symbol) {
	psym = sym_getsym(v);
	if (psym->id < maxint_)
	    o = psym->id;
    }
    node.op = o;
    node.val = v;
    node.nxt = n;
    node.marked = 0;
    return mem_put(&node);
}

static memrange FactorToMemory(data_t *cur)
{
    memrange i, j;
    memory_t *node;

    if (!cur)
	return 0;
    i = kons(cur->op, cur->val, 0);
    if (cur->op == typ_list) {
	j = TermToMemory(cur);
	node = mem_get(i);
	node->val = j;
    }
    return i;
}

static memrange TermToMemory(data_t *cur)
{
    memory_t *node;
    memrange i, j, k;

    if (!cur || (cur = cur->list) == 0)
	return 0;
    i = k = FactorToMemory(cur);
    while (cur) {
	cur = cur->next;
	j = FactorToMemory(cur);
	node = mem_get(i);
	i = node->nxt = j;
    }
    return k;
}

memrange ReadTerm()
{
    stack = 0;
    readterm();
    return TermToMemory(stack);
}

memrange ReadFactor()
{
    stack = 0;
    readfactor();
    return FactorToMemory(stack);
}
