/*
    module  : do_helpdetail.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "prims.h"
#include "ident.h"

/*
helpdetail  :  [ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
void do_helpdetail()
{
    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_list);
    helpdetail();
}
