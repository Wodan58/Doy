/*
    module  : aux_time.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "data.h"
#include "ident.h"

/*
gmtime  :  I  ->  T
Converts a time I into a list T representing universal time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is false; weekday is 1 = Monday ... 7 = Sunday.
*/
void aux_time(struct tm *tm)
{
    int num;
    data_t *cur = get(10);

    cur->op = typ_list;
    cur->list = cur + 1;
    cur->next = stack->next;
    stack = cur;
    for (num = 1; num <= 9; num++) {
	cur[num].op = typ_integer;
	cur[num].next = cur + num + 1;
    }
    cur[1].num = tm->tm_year + 1900;
    cur[2].num = tm->tm_mon + 1;
    cur[3].num = tm->tm_mday;
    cur[4].num = tm->tm_hour;
    cur[5].num = tm->tm_min;
    cur[6].num = tm->tm_sec;
    cur[7].op = typ_logical;
    cur[7].num = tm->tm_isdst;
    cur[8].num = tm->tm_yday;
    if ((num = tm->tm_wday) == 0)
	num = 7;
    cur[9].num = num;
    cur[9].next = 0;
}
