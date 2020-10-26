/*
    module  : joy0.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>
#include "defs.h"
#include "symbol.h"
#include "ident.h"
#include "memory.h"
#include "compile.h"
#include "convert.h"
#include "token.h"
#include "input.h"
#include "error.h"
#include "value.h"
#include "initsym.h"
#include "readlib.h"
#include "listing.h"
#include "stats.h"
#include "kons.h"
#include "interp.h"
#include "lookup.h"
#include "dump.h"

#define lib_filename	"42minjoy.lib"
#define list_filename	"42minjoy.lst"

int main(int argc, char *argv[])
{  /* main */
    static int c;
    int j, k = 1;
    symbol_t *psym;
    memory_t *node;

    atexit(perhapsstatistics);
    stat_start = clock();
    initlisting(list_filename);
    initialise();
    mem_init();
    lookup0();
    inp_init();
    if (argc > 1 && !strcmp(argv[1], "-c")) {
	argc--;
	k++;
	c++;
    }
    if (argc == 1)
	readlibrary(lib_filename);
    else {
	argc--;
	readlibrary(argv[k++]);
    }
    stat_lib = clock() - stat_start;
    if (writelisting > 2)
	for (j = 1; (psym = sym_getsym(j)) != 0; j++) {
	    fprintf(listing, "\"%-*.*s\" :\n", identlength, identlength,
		    psym->name);
	    if (psym->value) {
		WriteTerm(psym->value);
		WriteLine();
	    }
	}
    s = 0;
    dump = 0;
#ifndef NDEBUG
    DumpM(0);
#endif
    if (argc > 1)
	newfile(argv[k]);
    if (c)
	initcompile();
    setjmp(JL10);
    do {
	getsym();
	if (sym != def_end) {
	    programme = ReadFactor();
	    if (!c && writelisting > 2) {
		WriteString("interpreting:\n");
		WriteFactor(programme);
		WriteLine();
	    }
	    if (dump != 0) {
		Warning(WARNING, "dump error: should be empty!\n");
		WriteTerm(dump);
		WriteLine();
		dump = 0;
	    }
	    outlinelength = 0;
	    node = mem_get(programme);
	    if (c) {
		if (node->op == typ_list) {
		    compileterm(node->val, 1);
		    printf("\tcall\tnl\n");
		}
	    } else {
		joy(node->val);
		if (outlinelength > 0)
		    WriteLine();
	    }
	    if (!c && writelisting > 0 && outlinelength > 0)
		WriteLine();
	    if (!c && writelisting > 2) {
		WriteString("stack:\n");
		WriteTerm(s);
		WriteLine();
	    }
	}  /* IF */
    } while (sym != def_end);
    if (c)
	compilelib();
    finalise();
    return 0;
}
