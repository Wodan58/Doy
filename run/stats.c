/*
    module  : stats.c
    version : 1.3
    date    : 11/23/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "value.h"
#include "listing.h"
#include "stack.h"
#include "stats.h"
#include "chars.h"

clock_t stat_start, stat_lib, gc_clock;
unsigned long stat_gc;
double stat_kons, stat_ops, stat_calls;

char *ftoa(double x, char *str, int prec, int format, int chop);

static void writestatistics(FILE *f)
{
    char str[MAXBUF];
    long mem_size, dummy, stack_use;
    double stat_total = clock() - stat_start;

    mrep(&mem_size, &dummy, &dummy);
    srep(&dummy, &dummy, &stack_use);
    ftoa((double)stat_lib / CLOCKS_PER_SEC, str, 2, 'f', 0);
    fprintf(f, "%s seconds CPU to read library\n", str);
    ftoa((stat_total - stat_lib) / CLOCKS_PER_SEC, str, 2, 'f', 0);
    fprintf(f, "%s seconds CPU to execute\n", str);
    ftoa((double)gc_clock / CLOCKS_PER_SEC, str, 2, 'f', 0);
    fprintf(f, "%s seconds CPU for gc (=", str);
    ftoa(stat_total ? (100.0 * gc_clock) / stat_total : 0.0, str, 0, 'f', 1);
    fprintf(f, "%s%%)\n", str);
    fprintf(f, "%lu user nodes available\n", (unsigned long)mem_size);
    fprintf(f, "%lu garbage collections\n", stat_gc);
    ftoa(stat_kons, str, 0, 'f', 1);
    fprintf(f, "%s nodes used\n", str);
    ftoa(stat_calls, str, 0, 'f', 1);
    fprintf(f, "%s calls to joy interpreter\n", str);
    ftoa(stat_ops, str, 0, 'f', 1);
    fprintf(f, "%s operations executed\n", str);
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
    char str[MAXBUF];

    fflush(stdout);
    ftoa((double)(clock() - stat_start) / CLOCKS_PER_SEC, str, 2, 'f', 0);
    fprintf(f, "\n%s seconds CPU\n", str);
}

void finalise()
{
    /* finalise */
    fin(stderr);
    if (writelisting > 0 && listing)
	fin(listing);
    /* finalise */
}
