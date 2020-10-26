/*
    module  : do_formatf.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "chars.h"

/*
formatf  :  F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
void do_formatf()
{
    data_t *cur;
    int i, j, num;
    char str[MAXBUF], fmt[10];

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->next->next &&
	   stack->next->next->next && stack->op == typ_integer &&
	   stack->next->op == typ_integer &&
	   stack->next->next->op == typ_char &&
	   stack->next->next->next->op == typ_float);
    j = stack->num;		// precision
    stack = stack->next;
    i = stack->num;		// width
    stack = stack->next;
    strcpy(fmt, "%*.* ");	// format
    num = stack->num;
    assert(strchr("eEfgG", num));
    fmt[4] = num;
    stack = stack->next;
    snprintf(str, sizeof(str), fmt, i, j, stack->dbl);
    cur = get(1);
    cur->op = typ_string;
    cur->str = strdup(str);
    cur->next = stack->next;
    stack = cur;
}
