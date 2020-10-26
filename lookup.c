/*
    module  : lookup.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include "local.h"
#include "symbol.h"
#include "token.h"
#include "ident.h"
#include "initsym.h"

void lookup0()
{
    int i;
    long j;

    userindex = end_table - joy_table;
    for (i = 0; i < userindex; i++)
	if ((j = joy_table[i].value) == (long)do_stop)
	    sym_stop = i;
	else if (j == (long)do_true)
	    sym_true = i;
	else if (j == (long)do_false)
	    sym_false = i;
	else if (j == (long)do_nothing)
	    sym_nothing = i;
    undeferror = 0;
}

int lookup1(char *name)
{
    int low, mid, high, cmp;

    low = 0;			/* first line */
    high = userindex - 1;	/* last line */
    while (low <= high) {
	mid = low + (high - low) / 2;
	if ((cmp = strcmp(name, joy_table[mid].name)) == 0) {
	    sym = typ_symbol;
	    return val.num = mid;
	}
	if (cmp < 0)
	    high = mid - 1;
	else
	    low = mid + 1;
    }
    return -1;
}

char *lookup2(long num)
{
    static char buf[30];

    if (num < 0 || num >= userindex) {
	sprintf(buf, "(%ld)", num);
	return buf;
    }
    return joy_table[num].name;
}
