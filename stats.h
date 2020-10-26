/*
    module  : stats.h
    version : 1.2
    date    : 10/26/20
*/
extern clock_t stat_start, stat_lib, gc_clock;
extern unsigned long stat_gc;
extern double stat_kons, stat_ops, stat_calls;

void perhapsstatistics(void);
void finalise(void);
