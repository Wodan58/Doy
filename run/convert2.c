/*
    module  : convert2.c
    version : 1.3
    date    : 06/14/21

    Conversion from data_t to memory_t and vice versa.
*/
#include <stdio.h>
#include "defs.h"
#include "memory.h"
#include "data.h"
#include "ident.h"
#include "print.h"
#include "factor.h"
#include "symbol.h"
#include "input.h"
#include "listing.h"
#include "convert.h"

static void MemoryToTerm(memrange n);

static void MemoryToFactor(memrange n)
{
    int i, k;
    data_t *cur;
    memory_t *node;
    symbol_t *psym;

    node = mem_get(n);
    if (node->op == typ_list)
	MemoryToTerm(node->val);
    else {
	cur = get(1);
	if (node->op <= typ_file) {
	    cur->op = node->op;
	    cur->val = node->val;
	} else {
	    for (k = i = 0; (psym = sym_getsym(i)) != 0; i++)
		if (psym->id == node->op) {
		    k = i;
		    break;
		}
	    cur->op = typ_symbol;
	    cur->val = k;
	}
	cur->next = stack;
	stack = cur;
    }
}

static void MemoryToTerm(memrange n)
{
    data_t *cur;
    memory_t *node;

    cur = get(1);
    cur->op = typ_list;
    cur->list = 0;
    cur->next = stack;
    stack = cur;
    if (n > 0) {
	MemoryToFactor(n);
	stack->next->list = stack;
	stack = stack->next;
	stack->list->next = 0;
	node = mem_get(n);
	n = node->nxt;
	if (n > 0) {
	    cur = get(1);
	    cur->op = typ_list;
	    cur->list = stack->list;
	    cur->next = dump;
	    dump = cur;
	    while (n > 0) {
		MemoryToFactor(n);
		dump->list->next = stack;
		stack = stack->next;
		dump->list = dump->list->next;
		dump->list->next = 0;
		node = mem_get(n);
		n = node->nxt;
	    }
	    dump = dump->next;
	}
    }
}

void WriteTerm(memrange n)
{
    int leng;

    if (!n)
	return;
    stack = 0;
    MemoryToTerm(n);
    leng = outlinelength;
    printterm(stack, stdout);
    if (echoflag) {
	outlinelength = leng;
	printterm(stack, listing);
    }
}

void WriteFactor(memrange n)
{
    int leng;

    if (!n)
	return;
    stack = 0;
    MemoryToFactor(n);
    leng = outlinelength;
    printfactor(stack, stdout);
    if (echoflag) {
	outlinelength = leng;
	printfactor(stack, listing);
    }
}

void WriteLine()
{
    if (echoflag)
	echonewline(outlinelength);
    newline(stdout);
}

void WriteString(char *str)
{
    int leng;
    data_t cur;

    cur.op = typ_symbol;
    cur.str = str;
    leng = outlinelength;
    printfactor(&cur, stdout);
    if (echoflag) {
	outlinelength = leng;
	printfactor(&cur, listing);
    }
}

void WriteChar(int ch)
{
    char str[2];

    str[0] = ch;
    str[1] = 0;
    WriteString(str);
}
