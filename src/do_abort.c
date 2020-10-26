/*
    module  : do_abort.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "code.h"
#include "ident.h"
#include "symbol.h"
#include "nodes.h"
#include "local.h"

void setebp(long num);

/*
abort  :  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void do_abort()
{
    data_t node;
    long frame = 0;
    unsigned char *code;

    DEBUG(__FUNCTION__);
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
    for (;;) {
	if (node.op == typ_symbol && node.num == sym_stop) {
	    empty();
	    dump = dump1 = dump2 = dump3 = dump4 = dump5 = 0;
	    setebp(frame);
	    frame = (long)__builtin_frame_address(0);
	    ((long *)frame)[1] = (long)code;
	    return;
	}
	if (*code == 0xC3)
	    break;
	code += readcode((node_t *)code, &node);
    }
}
