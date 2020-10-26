/*
    module  : do_app4.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"

void do_unary4(void);

/*
unary4  :  X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Obsolescent.  == unary4
*/
void do_app4()
{
    DEBUG(__FUNCTION__);
    do_unary4();
}
