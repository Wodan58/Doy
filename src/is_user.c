/*
    module  : is_user.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "code.h"
#include "local.h"
#include "error.h"
#include "symbol.h"

/*
 is_user  :  ->
Undefined function, does nothing.
An error message is printed if the undeferror flag is 1.
*/
void is_user(int num)
{
    search_t *sym;

#if 0
    DEBUG(__FUNCTION__);
#endif
    sym = &joy_table[num];
    if (sym->value != 0)
	exeterm((data_t *)sym->value);
    else if (undeferror)
	ExecError(DEFINITION_EXPECTED, sym->name);
}
