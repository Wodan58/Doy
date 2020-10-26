/*
    module  : do_select.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"

void do_opcase(void);

/*
select  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void do_select()
{
    DEBUG(__FUNCTION__);
    do_opcase();
}
