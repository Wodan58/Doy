/*
    module  : do_conts.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "nodes.h"

void do_conts()
{
    long frame = 0;
    data_t *cur, node;
    unsigned char *code;

    DEBUG(__FUNCTION__);
    cur = get(1);
    cur->op = typ_list;
    cur->list = 0;
    cur->next = stack;
    stack = cur;
    for (;;) {
	if (!frame)
	    frame = (long)__builtin_frame_address(0);
	else
	    frame = *(long *)frame;
	if (!frame)
	    return;
	code = (unsigned char *)((long *)frame)[1];
	code += readcode((node_t *)code, &node);
	if (node.op != lib_)
	    break;
    }
    cur = get(1);
    cur->op = typ_list;
    cur->list = 0;
    cur->next = dump;
    dump = cur;
    for (;;) {
	cur = get(1);
	cur->op = node.op;
	cur->val = node.val;
	cur->next = 0;
	if (!dump->list)
	    dump->list = stack->list = cur;
	else
	    dump->list = dump->list->next = cur;
	if (*code == 0xC3)
	    break;
	code += readcode((node_t *)code, &node);
    }
    dump = dump->next;
}
