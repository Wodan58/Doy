/*
    module  : do_manual_list.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "prims.h"

/*
__manual_list  :  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
void do_manual_list()
{
    DEBUG(__FUNCTION__);
    manual_list();
}
