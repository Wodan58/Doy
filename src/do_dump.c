/*
    module  : do_dump.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
void do_dump()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_list;
    cur->list = dump;
    stack = cur;
}
