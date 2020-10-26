/*
    module  : stats.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "value.h"
#include "listing.h"
#include "stack.h"
#include "stats.h"

clock_t stat_start, stat_lib, gc_clock;
unsigned long stat_gc;
double stat_kons, stat_ops, stat_calls;

static void writestatistics(FILE *f)
{
    long mem_size, dummy, stack_use;
    double stat_total = clock() - stat_start;

    mrep(&mem_size, &dummy, &dummy);
    srep(&dummy, &dummy, &stack_use);
    fprintf(f, "%.2f seconds CPU to read library\n",
	    (double)stat_lib / CLOCKS_PER_SEC);
    fprintf(f, "%.2f seconds CPU to execute\n",
	    (stat_total - stat_lib) / CLOCKS_PER_SEC);
    fprintf(f, "%.2f seconds CPU for gc (=%.0f%%)\n",
	    (double)gc_clock / CLOCKS_PER_SEC,
	    stat_total ? (100.0 * gc_clock) / stat_total : 0.0);
    fprintf(f, "%lu user nodes available\n", (unsigned long)mem_size);
    fprintf(f, "%lu garbage collections\n", stat_gc);
    fprintf(f, "%.0f nodes used\n", stat_kons);
    fprintf(f, "%.0f calls to joy interpreter\n", stat_calls);
    fprintf(f, "%.0f operations executed\n", stat_ops);
    fprintf(f, "%lu bytes hardware stack used\n", (unsigned long)stack_use);
}

void perhapsstatistics()
{
    if (statistics > 0) {
	fflush(stdout);
	writestatistics(stderr);
	if (writelisting > 0 && listing)
	    writestatistics(listing);
    }
}

static void fin(FILE *f)
{
    fflush(stdout);
    fprintf(f, "\n%.2f seconds CPU\n",
	    (double)(clock() - stat_start) / CLOCKS_PER_SEC);
}

void finalise()
{
    /* finalise */
    fin(stderr);
    if (writelisting > 0 && listing)
	fin(listing);
    /* finalise */
}
