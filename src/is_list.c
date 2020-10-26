/*
    module  : is_list.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 list type  :  ->  [...]
The type of lists of values of any type (including lists),
or the type of quoted programs which may contain operators or combinators.
Literals of this type are written inside square brackets.
Examples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *].
*/
void is_list(data_t *list)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    reg(&list);
    cur = get(1);
    cur->op = typ_list;
    cur->list = list;
    cur->next = stack;
    stack = cur;
}
