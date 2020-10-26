/*
    module  : do_help.c
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
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
void do_help()
{
    int i, ch, x = 0;

    DEBUG(__FUNCTION__);
    for (i = userindex - 1; i >= 0; i--)
	if (joy_table[i].name && ((ch = *joy_table[i].name) != '_') && ch) {
	    if (x + strlen(joy_table[i].name) + 1 > MAXHLP) {
		putchar('\n');
		x = 0;
	    }
	    printf("%s ", joy_table[i].name);
	    x += strlen(joy_table[i].name) + 1;
	}
    putchar('\n');
}
