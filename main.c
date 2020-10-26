/*
    module  : main.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "boole.h"
#include "local.h"
#include "input.h"
#include "lookup.h"
#include "initsym.h"

int main()
{
    autoput = tracegc = TRUE;
    lookup0();
    inp_init();
    joy_text();
    return 0;
}
