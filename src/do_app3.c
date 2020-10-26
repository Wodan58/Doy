/*
    module  : do_app3.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"

void do_unary3(void);

/*
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Obsolescent.  == unary3
*/
void do_app3()
{
    DEBUG(__FUNCTION__);
    do_unary3();
}
