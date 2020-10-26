/*
    module  : do_argv.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "local.h"

/*
argv  :  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
void do_argv()
{
    int num;
    data_t *cur;

    DEBUG(__FUNCTION__);
    cur = get(g_argc + 1);
    cur->op = typ_list;
    cur->list = &cur[1];
    cur->next = stack;
    stack = cur;
    for (num = 1; num <= g_argc; num++) {
	cur[num].op = typ_string;
	cur[num].str = g_argv[num - 1];
	cur[num].next = cur + num + 1;
    }
    cur[g_argc].next = 0;
}
