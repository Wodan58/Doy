/*
    module  : duplo.c
    version : 1.3
    date    : 11/23/20
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "boole.h"
#include "local.h"
#include "chars.h"
#include "symbol.h"
#include "data.h"
#include "code.h"
#include "proc.h"
#include "print.h"
#include "stats.h"
#include "value.h"
#include "initsym.h"
#include "lookup.h"
#include "ident.h"
#include "listing.h"
#include "input.h"
#include "nodes.h"

int g_argc = 0;
char **g_argv = 0;

/*
    -d  defined symbols
    -u  undefined symbols
    -p  program
    -l  library
    -o  omit statistics
    -h  help
*/
int main(int argc, char *argv[])
{
    data_t cur;
    search_t *psym;
    int h = FALSE, d = FALSE, u = FALSE, p = FALSE, l = FALSE, i, j;

    setbuf(stdout, 0);
    autoput = tracegc = TRUE;
    statistics = TRUE;
    for (i = 1; i < argc; i++) {
	if (argv[i][0] != '-')
	    break;
	for (j = 1; argv[i][j]; j++)
	    switch (argv[i][j]) {
	    case 'h' :
		h = TRUE;
		break;

	    case 'd' :
		d = TRUE;
		break;

	    case 'u' :
		u = TRUE;
		break;

	    case 'p' :
		p = TRUE;
		break;

	    case 'l' :
		l = TRUE;
		break;

	    case 'o' :
		statistics = FALSE;
		break;
	    }
    }
    if (argv[i] && !isdigit(argv[i][0])) {
	if (!freopen(argv[i], "r", stdin)) {
	    fprintf(stderr, "failed to open the file '%s'.\n", argv[i]);
	    exit(0);
	}
	i++;
    }
    g_argc = argc - i + 1;
    g_argv = &argv[i - 1];
    argv[i - 1] = argv[0];
/*
    help summary
*/
    if (h) {
	fprintf(stderr, "%s  -  compiled at %s on %s\n",
		argv[0], __TIME__, __DATE__);
	fprintf(stderr, "Copyright 2013 by Ruurd Wiersma\n\n");
	fprintf(stderr, "d - print defined symbols\n");
	fprintf(stderr, "u - print undefined symbols\n");
	fprintf(stderr, "p - print program\n");
	fprintf(stderr, "l - print library\n");
	fprintf(stderr, "o - omit printing statistics\n");
	fprintf(stderr, "h - print this help summary\n");
    }
    lookup0();
/*
    defined symbols
*/
    cur.op = typ_symbol;
    if (d) {
	i = 0;
	for (psym = joy_table; psym < end_table; psym++)
	    if (psym->value != (long)is_user) {
		if (!i) {
		    i = 1;
		    cur.str = "defined: ";
		    printfactor(&cur, stdout);
		}
		cur.str = psym->name;
		printfactor(&cur, stdout);
		putch(SPACE, stdout);
	    }
	if (i)
	    putch('\n', stdout);
    }
/*
    undefined symbols
*/
    if (u) {
	i = 0;
	for (psym = joy_table; psym < end_table; psym++)
	    if (psym->value == (long)is_user) {
		if (!i) {
		    i = 1;
		    cur.str = "undefined: ";
		    printfactor(&cur, stdout);
		}
		cur.str = psym->name;
		printfactor(&cur, stdout);
		putch(SPACE, stdout);
	    }
	if (i)
	    putch('\n', stdout);
    }
/*
    program
*/
    if (p) {
	cur.str = "program: ";
	printfactor(&cur, stdout);
	printprogram((unsigned char *)joy_text, stdout);
	putch('\n', stdout);
    }
/*
    library
*/
    if (l) {
	i = 0;
	for (psym = joy_table; psym < end_table; psym++)
	    if (user(psym->value)) {
		if (!i) {
		    i = 1;
		    cur.str = "library:\n";
		    printfactor(&cur, stdout);
		} else {
		    putch(';', stdout);
		    putch('\n', stdout);
		}
		cur.str = psym->name;
		printfactor(&cur, stdout);
		cur.str = " == ";
		printfactor(&cur, stdout);
		printterm((data_t *)psym->value, stdout);
	    }
	if (i) {
	    putch('.', stdout);
	    putch('\n', stdout);
	}
    }
    if (h || d || u || p || l)
	return EXIT_SUCCESS;
    atexit(perhapsstatistics);
    stat_start = clock();
    initlisting("duplo.lst");
    inp_init();
    joy_text();
    finalise();
    return EXIT_SUCCESS;
}
