/*
    module  : 
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
void do_symtabindex()
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_integer;
    cur->num = userindex;
    cur->next = stack;
    stack = cur;
}
