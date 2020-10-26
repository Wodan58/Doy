/*
    module  : code.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "ident.h"
#include "proc.h"
#include "code.h"
#include "local.h"
#include "symbol.h"
#include "stats.h"

extern long joy_data[], end_data[];

/*
    The flex structure keeps track of how many items of flex_t can be allocated,
    how many items have been allocated previously, and how many are in use.
*/
typedef struct flex_t {
    int size;
    int prev;
    int used;
    long *tab;
} flex_t;

static flex_t root;

static void (*data[])() = {
    0,
    is_user,
    is_logical,
    is_char,
    is_integer,
    is_set,
    is_string,
    is_list,
    is_float,
    is_file
};

/*
    Allocate a node. When no nodes are available, the buffer that holds the
    nodes is automatically enlarged.
*/
void put(long num)
{
    if (root.size == root.used) {
	if ((root.size += root.prev) == 0) {
	    root.size = root.prev = 1;
	    root.tab = malloc(sizeof(long));
	} else {
	    root.prev = root.used;
	    root.tab = realloc(root.tab, root.size * sizeof(long));
	}
    }
    root.tab[root.used++] = num;
}

void rev(int start, int einde)
{
    long *cur, *buf, ch;

    cur = &root.tab[einde];
    buf = &root.tab[start];
    while (cur > buf) {
	ch = *cur;
	*cur-- = *buf;
	*buf++ = ch;
    }
}

/*
    Data is converted to code. Take note: typ_symbol is not always connected
    to an index in the symbol table, it can also be implemented with a string.
    Runtime symbols are ignored and not executed. This is possible, because
    there can be no new definitions at runtime.
*/
void proc(data_t *cur)
{
    int start, einde;

    for (start = root.used; cur; cur = cur->next)
	if (cur->op == typ_symbol) {
	    if (cur->num < userindex)
		put(cur->num);
	} else {
	    put(-cur->op);
	    put(cur->num);
	}
    if ((einde = root.used - 1) > start)
	rev(start, einde);
}

/*
    Deallocate a node. When the entire table has been processed, -1 is returned.
    De return value is long, assuming that a long is large enough to contain a
    pointer. If this assumption is not true, then a long must be used instead.
*/
long pop()
{
    if (!root.used)
	return -1;
    return root.tab[--root.used];
}

/*
    Execute a quotation or a procedure. The end is indicated with -1.
    Take note: it is not sure that the order of testing is the best possible.
*/
void loop()
{
    long ch, num;

    while ((ch = pop()) != -1)
	if (ch < 0)
	    (*data[-ch])(pop());
	else if (ch >= userindex)
	    (*(proc_t)ch)();
	else if ((num = joy_table[ch].value) == 0)
	    is_user(ch);
	else if (user(num))
	    proc((data_t *)num);
	else
	    (*(proc_t)num)();
}

int user(long num)
{
    return num >= (long)joy_data && num < (long)end_data;
}

/*
    Execute a quotation. If within a quotation another quotation is executed,
    then exeterm is called recursively. Normal procedures are handled within
    loop and not called recursively.
*/
void exeterm(data_t *cur)
{
    stat_calls++;
    put(-1);
    proc(cur);
    loop();
}

int used()
{
    return root.used;
}

long peek(int i)
{
    return root.tab[i];
}

void poke(int i, long num)
{
    root.tab[i] = num;
}

void empty()
{
    root.used = 0;
}
