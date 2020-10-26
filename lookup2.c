/*
    module  : lookup2.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol.h"
#include "error.h"
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

/*
    sym > 0 : reswords[]
    sym = 0 : id > 0 : stdidents[]
	      id = 0 : value > 0 : table[]
		       value = 0 : unknown
*/
int lookup1(char *name)
{
    int leng;
    symbol_t *psym;
    char str[MAXSTR];

    if ((val.num = sym_lookup(name)) == 0)
	ExecError(DEFINITION_EXPECTED, name);
    psym = sym_getsym(val.num);
    if (psym->prime && sym_default()) {
	sprintf(str, "%d", psym->prime);
	leng = strlen(psym->name) + strlen(str) + 2;
	name = malloc(leng);
	sprintf(name, "%s#%s", psym->name, str);
	if ((val.num = sym_lookup(name)) == 0)
	    ExecError(DEFINITION_EXPECTED, name);
	psym = sym_getsym(val.num);
    }
    sym = psym->sym;
    return psym->id;
}  /* lookup1 */

char *lookup2(long num)
{
    symbol_t *psym;

    psym = sym_getsym(num);
    return num >= 0 ? psym->name : "(null)";
}
