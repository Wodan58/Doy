/*
    module  : do_fread.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fread  :  S I  ->  L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
void do_fread()
{
    char *str;
    int i, num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_integer &&
	   stack->next->op == typ_file && stack->next->fp);
    num = stack->num;
    str = malloc(num);
    stack = stack->next;
    num = fread(str, 1, num, stack->fp);
    cur = get(num + 1);
    cur->op = typ_list;
    cur->list = &cur[1];
    cur->next = stack;
    stack = cur;
    for (i = 1; i <= num; i++) {
	cur[i].op = typ_integer;
	cur[i].num = str[i - 1] & 0xFF;
	cur[i].next = &cur[i + 1];
    }
    cur[num].next = 0;
    free(str);
}
