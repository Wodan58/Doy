/*
    module  : do_get.c
    version : 1.2
    date    : 10/26/20
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
    redirect(stdin);
    getsym();
    readfactor();
}
