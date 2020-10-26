/*
    module  : lookup1.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include "symbol.h"
#include "token.h"
#include "value.h"
#include "local.h"
#include "chars.h"
#include "lookup.h"

void lookup0()
{
    radix = 2;
    userindex = MAXTAB;
    sym_stop = sym_lookup(".");
    sym_true = sym_lookup("true");
    sym_false = sym_lookup("false");
    sym_nothing = sym_lookup("nothing");
    undeferror = 0;
}

int lookup1(char *name)
{
    symbol_t *psym;

    val.num = sym_lookup(strdup(name));
    psym = sym_getsym(val.num);
    sym = psym->sym;
    return psym->id;
}

char *lookup2(long num)
{
    symbol_t *psym;

    psym = sym_getsym(num);
    return num >= 0 ? psym->name : "(null)";
}
