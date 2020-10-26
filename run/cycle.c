/*
    module  : cycle.c
    version : 1.2
    date    : 10/26/20

	int ExpCycle(memrange *prog)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include "chars.h"
#include "ident.h"
#include "memory.h"
#include "token.h"
#include "error.h"
#include "symbol.h"
#include "boole.h"
#include "value.h"
#include "convert.h"
#include "listing.h"
#include "factor2.h"
#include "cycle.h"

static int Prime(symbol_t *psym)
{
    int leng;
    symbol_t *nsym;
    char str[MAXSTR], *name;

    sprintf(str, "%d", ++psym->prime);
    leng = strlen(psym->name) + strlen(str) + 2;
    name = malloc(leng);
    sprintf(name, "%s#%s", psym->name, str);
    leng = sym_lookup(name);
    nsym = sym_getsym(leng);
    nsym->value = psym->value;
    nsym->used = 1;
    return leng;
}

static int ExpAtomic()
{
    symbol_t *psym;
    int loc = val.num;

    if (sym != typ_symbol)
	ExpError(PASS_2_IDENTIFIER_EXPECTED);
    psym = sym_getsym(loc);
    if (writelisting > 8)
	fprintf(listing, "seen : %s\n", psym->name);
    if (psym->id) {
	Warning(WARNING_OVERWRITING_INBUILT, psym->name);
	loc = Prime(psym);
    } else if (psym->used) {
	Warning(WARNING_REDEFINITION, psym->name);
	loc = Prime(psym);
    }
    sym_section(def_equal);
    getsym();			// to get past SYMBOL
    return loc;
}

static void ExpEqual()
{
    if (sym != def_equal)
	ExpError(PASS_2_EQUAL_EXPECTED);
    getsym();			// to get past ==
}

/*
simple-definition   ::= atomic-symbol "==" term
*/
static void ExpDefinition()
{
    int loc;
    memrange first;
    symbol_t *psym;

    loc = ExpAtomic();
    ExpEqual();
    readterm(&first);
    psym = sym_getsym(loc);
    psym->id = lib_;
    psym->value = first;
    if (writelisting > 8) {
	WriteTerm(first);
	WriteLine();
    }
}

/*
definition-sequence ::= simple-definition { ";" simple-definition }
*/
static void ExpDefinitionSequence()
{
    int prev;

    if (sym == def_module || sym == def_private || sym == def_public)
	return;
    ExpDefinition();
    while (sym == def_end || sym == ';') {
	sym_section(prev = sym);
	getsym();		// to get past '.' or ';'
	if (prev == ';') {
	    if (sym == def_end)
		continue;
	    if (sym == def_module || sym == def_private || sym == def_public)
		return;
	    ExpDefinition();
	}
    }
}

static void ExpEndDef()
{
    while (sym == def_end || sym == ';')
	getsym();		// to get past '.' or ';'
}

/*
compound-definition ::= [ "MODULE" atomic-symbol ]
			[ "PRIVATE" definition-sequence ]
			[ "PUBLIC" definition-sequence ]
			( "END" | "." )
*/
static void ExpCompoundDefinition()
{
    while (sym == def_module || sym == def_private || sym == def_public) {
	if (sym == def_module) {
	    sym_section(sym);
	    getsym();		// to get past MODULE
	    ExpAtomic();
	}
	if (sym == def_private) {
	    sym_section(sym);
	    getsym();		// to get past PRIVATE or HIDE
	    ExpDefinitionSequence();
	}
	if (sym == def_public) {
	    sym_section(sym);
	    getsym();		// to get past PUBLIC or IN
	    ExpDefinitionSequence();
	}
    }
    ExpEndDef();
}

static void ExpEndProg()
{
    while (sym == ';')
	getsym();		// to get past '.' or ';'
    if (sym == def_end)
	getsym();
}

/*
cycle		    ::= { compound-definition | term ( "." | "END" ) }
*/
int ExpCycle(memrange *prog)
{
    while (sym != EOF)
	if (sym == def_module || sym == def_private || sym == def_public)
	    ExpCompoundDefinition();
	else {
	    readterm(prog);
	    if (sym == EOF)
		break;
	    ExpEndProg();
	    return TRUE;
	}
    return FALSE;
}
