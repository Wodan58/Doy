/*
    module  : factor2.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "defs.h"
#include "memory.h"
#include "symbol.h"
#include "token.h"
#include "ident.h"
#include "kons.h"
#include "error.h"
#include "factor2.h"

/*
factor		    ::= atomic-symbol | boolean-constant
			| character-constant | integer-constant
			| float-constant | string-constant
			| "{" { character-constant | integer-constant } "}"
			| "[" term "]
*/
static void readfactor(memrange *where)
{
    memory_t *pmem;
    memrange first;

    *where = 0;
    switch (sym) {
    case '{' :
	ExpSet();
	/* continue */

    case typ_logical  :
    case typ_char     :
    case typ_integer  :
    case typ_float    :
    case typ_string   :
    case typ_symbol   :
    case typ_function :
	*where = kons(sym, val.num, 0);
	getsym();
	break;

    case '[' :
	*where = kons(typ_list, 0, 0);
	getsym();
	if (sym != ']') {
	    readterm(&first);
	    pmem = mem_get(*where);
	    pmem->val = first;
	    if (sym != ']')
		ExpError(RIGHT_BRACKET_EXPECTED);
	}
	getsym();
	break;

    case def_module  :
    case def_private :
    case def_public  :
    case def_end     :
    case ')' :
    case ';' :
    case ']' :
    case EOF :
	break;

    default  :
	ExpError(INTERNAL_IN_READFACTOR);
	break;
    }
}

/*
term		    ::= { factor }
*/
void readterm(memrange *first)
{
    memory_t *pmem;
    memrange cur, next;

    readfactor(first);
    cur = *first;
    while (sym != def_module && sym != def_private && sym != def_public &&
	   sym != def_end && sym != ')' && sym != ';' && sym != ']' &&
	   sym != EOF) {
	readfactor(&next);
	pmem = mem_get(cur);
	cur = pmem->nxt = next;
    }
}
