/*
    module  : do_fold.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"

void do_swapd(void);
void do_step(void);

/*
fold  :  A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
void do_fold()
{
    DEBUG(__FUNCTION__);
    do_swapd();
    do_step();
}
