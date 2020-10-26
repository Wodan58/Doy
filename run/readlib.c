/*
    module  : readlib.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "memory.h"
#include "symbol.h"
#include "ident.h"
#include "token.h"
#include "value.h"
#include "input.h"
#include "error.h"
#include "lookup.h"
#include "listing.h"
#include "convert.h"
#include "readlib.h"

void readlibrary(char *str)
{
    int loc;
    memrange first;
    symbol_t *psym;

    if (writelisting > 5)
	fprintf(listing, "first pass through library:\n");
    newfile(str);
    do {
	getsym();
	if (writelisting > 8)
	    fprintf(listing, "seen : %-*.*s\n", identlength, identlength,
		    lookup2(val.num));
	if (sym != typ_symbol)
	    ExpError(PASS_2_IDENTIFIER_EXPECTED);
	loc = val.num;
	getsym();
	if (sym != def_equal)
	    ExpError(PASS_2_EQUAL_EXPECTED);
	getsym();
	first = ReadTerm();
	psym = sym_getsym(loc);
	psym->id = lib_;
	psym->value = first;
	if (writelisting > 8) {
	    WriteTerm(first);
	    WriteLine();
	}
    } while (sym != def_end);
}  /* readlibrary */
