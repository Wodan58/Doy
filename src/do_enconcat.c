/*
    module  : do_enconcat.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "set32.h"

/*
enconcat  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
void do_enconcat()
{
    int i, j, num;
    data_t *cur, *node;
    char *str, *ptr, *tmp;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == stack->next->op);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	stack = stack->next;
	i = stack->num;
	stack = stack->next;
	num = stack->num;
	cur = get(1);
	cur->op = typ_set;
	cur->num = set_bit(i | j, num);
	cur->next = stack->next;
	stack = cur;
	break;

    case typ_string :
	ptr = stack->str;
	j = strlen(ptr);
	stack = stack->next;
	str = stack->str;
	i = strlen(str);
	stack = stack->next;
	num = stack->num;
	tmp = malloc(i + j + 2);
	strcpy(tmp, str);
	tmp[i] = num;
	strcpy(&tmp[i + 1], ptr);
	cur = get(1);
	cur->op = typ_string;
	cur->str = tmp;
	cur->next = stack->next;
	stack = cur;
	break;

    case typ_list :
	for (i = 0, node = stack->next->list; node; node = node->next)
	    i++;
	cur = get(i + 2);
	for (i = 0, node = stack->next->list; node; node = node->next, i++) {
	    cur[i + 1].op = node->op;
	    cur[i + 1].val = node->val;
	    cur[i + 1].next = &cur[i + 2];
	}
	node = stack->next->next;
	cur[i + 1].op = node->op;
	cur[i + 1].val = node->val;
	cur[i + 1].next = stack->list;
	cur->op = typ_list;
	cur->list = &cur[1];
	cur->next = node->next;
	stack = cur;
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
}
