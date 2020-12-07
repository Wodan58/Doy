/*
    module  : do_get.c
    version : 1.3
    date    : 11/23/20
*/
#include <stdio.h>
#include "data.h"
#include "token.h"
#include "input.h"
#include "factor.h"

/*
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
void do_get()
{
    DEBUG(__FUNCTION__);
    fflush(stdout);
    getsym();
    readfactor();
}
