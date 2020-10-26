/*
    module  : do_stop.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "print.h"
#include "local.h"

void do_put(void);

/*
stop  :  X  ->
Writes X to output, pops X off stack.
*/
void do_stop()
{
    DEBUG(__FUNCTION__);
    if (!stack)
	return;
    switch (autoput) {
    case 2 :
	printstack(stack, stdout);
	newline(stdout);
	break;

    case 1 :
	do_put();
	newline(stdout);
	break;
    }
    fflush(stdout);
}
