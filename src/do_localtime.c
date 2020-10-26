/*
    module  : do_localtime.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "data.h"
#include "ident.h"

void aux_time(struct tm *tm);

/*
localtime  :  I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
void do_localtime()
{
    struct tm *tm;

    DEBUG(__FUNCTION__);
    assert(stack && stack->op == typ_integer);
    tm = localtime((time_t *)&stack->num);
    aux_time(tm);
}
