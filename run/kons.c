/*
    module  : kons.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "memory.h"
#include "symbol.h"
#include "convert.h"
#include "ident.h"
#include "value.h"
#include "stats.h"
#include "listing.h"
#include "stats.h"
#include "kons.h"

extern char *standardident_NAMES[];

memrange programme, s, /* stack */ dump;

static void wn(FILE *f, memrange n)
{
    symbol_t *psym;
    memory_t *node;

    node = mem_get(n);
    fprintf(f, "%5ld %-*.*s", (long)n, identlength, identlength,
	    standardident_NAMES[node->op]);
    if (node->op == typ_string)
	fprintf(f, " %s ", (char *)node->val);
    else
	fprintf(f, " %10ld ", node->val);
    fprintf(f, "%10ld %c", (long)node->nxt, node->marked ? 'T' : 'F');
    if (node->op == lib_) {
	psym = sym_getsym(node->val);
	fprintf(f, "   %-*.*s %4ld", identlength, identlength,
		psym->name, psym->value);
    }
    putc('\n', f);
}

static void writenode(memrange n)
{
    wn(stdout, n);
    if (writelisting > 0) {
	putc('\t', listing);
	wn(listing, n);
    }
}  /* writenode */

memrange kons(standardident o, long v, memrange n)
{
    memrange i;
    memory_t node;

    node.op = o;
    node.val = v;
    node.nxt = n;
    node.marked = 0;
    i = mem_put(&node);
    if (writelisting > 4)
	writenode(i);
    stat_kons++;
    return i;
}  /* kons */
