/*
    module  : is_user.c
    version : 1.3
    date    : 11/23/20
*/
#include <stdio.h>
#include "data.h"
#include "code.h"
#include "local.h"
#include "error.h"
#include "symbol.h"
#include "proc.h"

/*
 is_user  :  ->
Undefined function, does nothing.
An error message is printed if the undeferror flag is 1.
*/
void is_user(long num)
{
    search_t *sym;

#if 0
    DEBUG(__FUNCTION__);
#endif
    sym = &joy_table[num];
    if (sym->value != 0)
	exeterm((data_t *)sym->value);
    else {
	if (undeferror)
	    ExecError(DEFINITION_EXPECTED, sym->name);
	is_integer(0);
    }
}
