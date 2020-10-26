/*
    module  : spasm.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"
#include "memory.h"
#include "initsym.h"
#include "input.h"
#include "token.h"
#include "compile.h"
#include "cycle.h"
#include "strings.h"
#include "listing.h"
#include "stats.h"
#include "lookup.h"
#include "dump.h"

int main(int argc, char *argv[])
{
    memrange program;

    atexit(perhapsstatistics);
    stat_start = clock();
    initlisting("spasm.lst");
    initialise();
    mem_init();
    str_init();
    lookup0();
    inp_init();
    if (argc > 1)
	firstfile(argv[1]);
    else {
	fprintf(stderr, "spasm  -  compiled at %s on %s\n", __TIME__, __DATE__);
	fprintf(stderr, "Copyright 2013 by Ruurd Wiersma\n");
    }
    getsym();
    initcompile();
    while (ExpCycle(&program)) {
	compileterm(program, 1);
	compilestop();
    }
    compilelib();
    finalise();
#ifndef NDEBUG
    DumpM(0);
#endif
    return 0;
}
