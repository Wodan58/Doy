/*
    module  : do_fseek.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
fseek  :  S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
void do_fseek()
{
    data_t *cur;
    int num, pos;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next &&
	   stack->op == typ_integer && stack->next->op == typ_integer &&
	   stack->next->next->op == typ_file && stack->next->next->fp);
    num = stack->num;
    stack = stack->next;
    pos = stack->num;
    stack = stack->next;
    cur = get(1);
    cur->op = typ_logical;
    cur->num = fseek(stack->fp, pos, num) != 0;
    cur->next = stack;
    stack = cur;
}
