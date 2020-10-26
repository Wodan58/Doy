/*
    module  : do_concat.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

/*
concat  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
void do_concat()
{
    int i, j;
    data_t *cur, *node;
    char *str, *ptr, *tmp;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == stack->next->op);
    switch (stack->op) {
    case typ_set :
	j = stack->num;
	stack = stack->next;
	i = stack->num;
	cur = get(1);
	cur->op = typ_set;
	cur->num = i | j;
	cur->next = stack->next;
	stack = cur;
	break;

    case typ_string :
	ptr = stack->str;
	j = strlen(ptr);
	stack = stack->next;
	str = stack->str;
	i = strlen(str);
	tmp = malloc(i + j + 1);
	strcpy(tmp, str);
	strcpy(tmp + i, ptr);
	cur = get(1);
	cur->op = typ_string;
	cur->str = tmp;
	cur->next = stack->next;
	stack = cur;
	break;

    case typ_list :
	if (!stack->list)
	    stack = stack->next;
	else if ((node = stack->next->list) == 0) {
	    cur = get(1);
	    cur->op = typ_list;
	    cur->list = stack->list;
	    cur->next = stack->next->next;
	    stack = cur;
	} else {
	    for (i = 0; node; node = node->next)
		i++;
	    cur = get(i + 1);
	    for (i = 0, node = stack->next->list; node; node = node->next) {
		cur[i + 1].op = node->op;
		cur[i + 1].val = node->val;
		cur[i + 1].next = &cur[i + 2];
		i++;
	    }
	    cur[i].next = stack->list;
	    cur->op = typ_list;
	    cur->list = &cur[1];
	    cur->next = stack->next->next;
	    stack = cur;
	}
	break;

    default :
	assert(stack->op == typ_set || stack->op == typ_string ||
	       stack->op == typ_list);
	break;
    }
}
