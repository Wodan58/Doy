/*
    module  : do_app2.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"

void do_unary2(void);

/*
unary2  :  X1 X2 [P]  ->  R1 R2
Obsolescent.  == unary2
*/
void do_app2()
{
    DEBUG(__FUNCTION__);
    do_unary2();
}
