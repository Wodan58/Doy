/*
    module  : do_quit.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

/*
quit  :  ->
Exit from Joy.
*/
void do_quit()
{
    DEBUG(__FUNCTION__);
    exit(EXIT_SUCCESS);
}
