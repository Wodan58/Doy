/*
    module  : interp.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <time.h>
#include "defs.h"
#include "memory.h"
#include "ident.h"
#include "error.h"
#include "symbol.h"
#include "convert.h"
#include "stats.h"
#include "kons.h"
#include "value.h"
#include "input.h"
#include "token.h"
#include "interp.h"

typedef unsigned char boolean;

jmp_buf JL10;

static void binary(standardident o, long v)
{
    memory_t *node = mem_get(s);

    s = kons(o, v, mem_get(node->nxt)->nxt);
}

static memrange ok(memrange x)
{
    if (x < 1)
	Warning(WARNING, "null address being referenced");
    return x;
}  /* ok */

static standardident o(memrange x)
{
    memory_t *node = mem_get(ok(x));

    return node->op;
}

static boolean b(memrange x)
{
    memory_t *node = mem_get(ok(x));

    return (boolean)(node->val > 0);
}

static long i(memrange x)
{
    memory_t *node = mem_get(ok(x));

    if (node->op == typ_integer)
	return node->val;
    Warning(WARNING, "integer value required");
    longjmp(JL10, 1);
}  /* i */

static memrange l(memrange x)
{
    memory_t *node = mem_get(ok(x));

    if (node->op == typ_list)
	return node->val;
    Warning(WARNING, "list value required");
    longjmp(JL10, 1);
}  /* l */

static memrange n(memrange x)
{
    memory_t *node = mem_get(ok(x));

    if (node->nxt >= 0)
	return node->nxt;
    Warning(WARNING, "negative next value");
    longjmp(JL10, 1);
}  /* n */

static long v(memrange x)
{
    memory_t *node = mem_get(ok(x));

    return node->val;
}

void joy(memrange nod)
{
    static symbol_t *psym1, *psym2;
    static memory_t *node;

    memrange temp1, temp2;

    while (nod > 0) {  /* WHILE */
	node = mem_get(nod);
	if (writelisting > 3) {
	    WriteString("joy: ");
	    WriteFactor(nod);
	    WriteLine();
	}
	if (writelisting > 4) {
	    WriteString("stack: ");
	    WriteTerm(s);
	    WriteLine();
	    WriteString("dump: ");
	    WriteTerm(dump);
	    WriteLine();
	}
	nod = node->nxt;
	switch (node->op) {
	case nothing_:
	case typ_logical:
	case typ_char:
	case typ_integer:
	case typ_list:
	    s = kons(node->op, node->val, s);
	    break;

	case true_:
	case false_:
	    s = kons(typ_logical, node->op == true_, s);
	    break;

	case pop_:
	    s = n(s);
	    break;

	case dup_:
	    s = kons(o(s), v(s), s);
	    break;

	case swap_:
	    s = kons(o(n(s)), v(n(s)), kons(o(s), v(s), n(n(s))));
	    break;

	case stack_:
	    s = kons(typ_list, s, s);
	    break;

	case unstack_:
	    s = l(s);
	    break;

	/* OPERATIONS: */
	case not_:
	    s = kons(typ_logical, !b(s), n(s));
	    break;

	case mul_:
	    binary(typ_integer, i(n(s)) * i(s));
	    break;

	case add_:
	    binary(typ_integer, i(n(s)) + i(s));
	    break;

	case sub_:
	    binary(typ_integer, i(n(s)) - i(s));
	    break;

	case div_:
	    binary(typ_integer, i(n(s)) / i(s));
	    break;

	case and_:
	    binary(typ_logical, b(n(s)) & b(s));
	    break;

	case or_:
	    binary(typ_logical, b(n(s)) | b(s));
	    break;

	case lss_:
	    if (o(s) <= typ_symbol) {
		psym1 = sym_getsym(v(n(s)));
		psym2 = sym_getsym(v(s));
		binary(typ_logical, strcmp(psym1->name, psym2->name) < 0);
	    }
	    else
		binary(typ_logical, v(n(s)) < v(s));
	    break;

	case eql_:
	    binary(typ_logical, v(n(s)) == v(s));
	    break;

	case sametype_:
	    binary(typ_logical, o(n(s)) == o(s));
	    break;

	case cons_:
	    if (o(n(s)) == nothing_)
		s = kons(typ_list, l(s), n(n(s)));
	    else
		s = kons(typ_list, kons(o(n(s)), v(n(s)), v(s)), n(n(s)));
	    break;

	case uncons_:
	    if (!mem_get(s)->val)
		s = kons(typ_list, 0, kons(nothing_, nothing_, n(s)));
	    else
		s = kons(typ_list, n(l(s)), kons(o(l(s)), v(l(s)), n(s)));
	    break;

	case select_:
	    temp1 = l(s);
	    while (o(l(temp1)) != o(n(s)))
		temp1 = n(temp1);
	    s = kons(typ_list, n(l(temp1)), n(s));
	    break;

	case index_:
	    if (v(n(s)) < 1)
		s = kons(o(l(s)), v(l(s)), n(n(s)));
	    else
		s = kons(o(n(l(s))), v(n(l(s))), n(n(s)));
	    break;

	case body_:
	    s = kons(typ_list, sym_getsym(v(s))->value, n(s));
	    break;

	case put_:
	    WriteFactor(s);
	    s = n(s);
	    break;

	case putch_:	/* R.W. */
	    WriteChar(v(s));
	    s = n(s);
	    break;

	case get_:
	    getsym();
	    temp1 = ReadFactor();
	    s = kons(o(temp1), v(temp1), s);
	    break;

	case getch_:	/* R.W. */
	    getch();
	    s = kons(typ_integer, ch, s);
	    break;

	/* COMBINATORS: */
	case i_:
	    temp1 = s;
	    s = n(s);
	    joy(l(temp1));
	    break;

	case dip_:
	    dump = kons(o(n(s)), v(n(s)), dump);
	    dump = kons(typ_list, l(s), dump);
	    s = n(n(s));
	    joy(l(dump));
	    dump = n(dump);
	    s = kons(o(dump), v(dump), s);
	    dump = n(dump);
	    break;

	case step_:
	    dump = kons(o(s), l(s), dump);
	    dump = kons(o(n(s)), l(n(s)), dump);
	    temp1 = l(s);
	    temp2 = l(n(s));
	    s = n(n(s));
	    while (temp2 > 0) {
		s = kons(o(temp2), v(temp2), s);
		joy(temp1);
		temp2 = n(temp2);
	    }
	    dump = n(n(dump));
	    break;

	case lib_:
	case typ_symbol:
	    joy(sym_getsym(node->val)->value);
	    break;

	default:
	    ExpError(INTERNAL_IN_READFACTOR);
	    break;
	}  /* CASE */
	stat_ops++;
    }
    stat_calls++;
}  /* joy */
