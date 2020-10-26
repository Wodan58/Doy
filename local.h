/*
    module  : local.h
    version : 1.2
    date    : 10/26/20
*/
extern int userindex;
extern int sym_stop;
extern int sym_true;
extern int sym_false;
extern int sym_nothing;
extern int autoput;
extern int undeferror;
extern int tracegc;
extern int g_argc;
extern char **g_argv;

/*
int ch, echoflag, outlinelength			- input.h
int writelisting, statistics, radix, trace	- value.h
int sym; value_t val				- token.h
FILE *listing					- listing.h
search_t joy_table[], end_table[]		- symbol.h
jmp_buf JL10					- interp.h
clock_t stat_start, stat_lib, gc_clock		- stats.h
long stat_gc					- stats.h
double stat_kons, stat_ops, stat_calls		- stats.h
data_t *stack, *dump, *dump1-5			- data.h
memrange programme, s, dump			- kons.h
*/
