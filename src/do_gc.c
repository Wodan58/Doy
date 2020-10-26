/*
    module  : do_gc.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"

/*
gc  :  ->
Initiates garbage collection.
*/
void do_gc()
{
    DEBUG(__FUNCTION__);
    gc();
}
