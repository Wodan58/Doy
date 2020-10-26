/*
    module  : do_x.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "code.h"
#include "ident.h"

/*
x  :  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
void do_x()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list);
    exeterm(stack->list);
}
