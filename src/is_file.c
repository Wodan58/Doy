/*
    module  : is_file.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"

/*
 file type  :  ->  FILE:
The type of references to open I/O streams,
typically but not necessarily files.
The only literals of this type are stdin, stdout, and stderr.
*/
void is_file(FILE *fp)
{
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_file;
    cur->fp = fp;
    cur->next = stack;
    stack = cur;
}
