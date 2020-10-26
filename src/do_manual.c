/*
    module  : do_manual.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "prims.h"

/*
manual  :  ->
Writes this manual of all Joy primitives to output file.
*/
void do_manual()
{
    DEBUG(__FUNCTION__);
    make_manual(PLAIN);
}
