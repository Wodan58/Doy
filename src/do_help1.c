/*
    module  : do_help1.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "local.h"
#include "chars.h"
#include "symbol.h"

/*
_help  :  ->
Lists all hidden symbols in library and then all hidden builtin symbols.
*/
void do_help1()
{
    int i, x = 0;

    DEBUG(__FUNCTION__);
    putchar('\n');
    for (i = userindex - 1; i >= 0; i--)
	if (joy_table[i].name && *joy_table[i].name == '_') {
	    if (x + strlen(joy_table[i].name) + 1 > MAXHLP) {
		putchar('\n');
		x = 0;
	    }
	    printf("%s ", joy_table[i].name);
	    x += strlen(joy_table[i].name) + 1;
	}
    putchar('\n');
}
