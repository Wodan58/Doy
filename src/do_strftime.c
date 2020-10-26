/*
    module  : do_strftime.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "data.h"
#include "ident.h"
#include "chars.h"

void aux_decode(struct tm *tm);

/*
strftime  :  T S1  ->  S2
Formats a list T in the format of localtime or gmtime
using string S1 and pushes the result S2.
*/
void do_strftime()
{
    data_t *cur;
    struct tm tm;
    char str[MAXSTR], *ptr;

    DEBUG(__FUNCTION__);
    assert(stack && stack->next && stack->op == typ_string &&
	   stack->next->op == typ_list);
    ptr = stack->str;
    stack = stack->next;
    aux_decode(&tm);
    strftime(str, sizeof(str), ptr, &tm);
    cur = get(1);
    cur->op = typ_string;
    cur->str = strdup(str);
    cur->next = stack->next;
    stack = cur;
}
