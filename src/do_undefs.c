/*
    module  : do_undefs.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "local.h"
#include "symbol.h"

/*
undefs  :  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
void do_undefs()
{
    data_t *cur;
    int i, num = 0;

    DEBUG(__FUNCTION__);
    for (i = userindex - 1; i >= 0; i--)
	if (joy_table[i].name && *joy_table[i].name != 0 &&
			*joy_table[i].name != '_' && joy_table[i].value == 0)
	    num++;
    cur = get(num + 1);
    cur->op = typ_list;
    cur->list = &cur[1];
    cur->next = stack;
    stack = cur;
    for (i = userindex - 1; i >= 0; i--)
	if (joy_table[i].name && *joy_table[i].name != 0 &&
			*joy_table[i].name != '_' && joy_table[i].value == 0) {
	    cur[i + 1].op = typ_string;
	    cur[i + 1].str = joy_table[i].name;
	    cur[i + 1].next = &cur[i + 2];
	}
    cur[num].next = 0;
}
