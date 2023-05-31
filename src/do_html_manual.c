/*
    module  : do_html_manual.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "prims.h"

/*
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
void do_html_manual()
{
    DEBUG(__FUNCTION__);
    make_manual(HTML);
}
