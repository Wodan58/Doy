/*
    module  : debug.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "ident.h"
#include "stats.h"
#include "value.h"
#include "print.h"

void debug(const char *name)
{
    data_t cur;

    stat_ops++;
    if (writelisting) {
	cur.op = typ_symbol;
	if (writelisting > 1) {
	    printstack(stack, stdout);		/* stack : */
	    cur.str = " . ";
	    printfactor(&cur, stdout);
	}
	cur.str = (char *)(name + 3);		/* joy   : */
	printfactor(&cur, stdout);
	newline(stdout);
	fflush(stdout);
    }
}
