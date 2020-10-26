/*
    module  : 
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "prims.h"

/*
__latex_manual  :  ->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
void do_latex_manual()
{
    DEBUG(__FUNCTION__);
    make_manual(LATEX);
}
