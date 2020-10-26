/*
    module  : data.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "ident.h"
#include "stats.h"
#include "code.h"

/*
    The flag indicates whether the next time a larger buffer must be allocated
    or that an equally large buffer is sufficient.
*/
enum flag_t {
    ALLOC_MORE,
    ALLOC_SAME,
    DONT_ALLOC
};

/*
    This structure keeps track how many items of data_t are allocated, how many
    are in use and whether the next time that garbage collection occurs, the
    same number or more nodes must be allocated.
*/
typedef struct flex_t {
    int size;
    int prev;
    int used;
    enum flag_t flag;
    data_t *old, *tab;
} flex_t;

static flex_t root;
static data_t **parms, *next = 0;
data_t *stack = 0, *dump = 0, *dump1 = 0, *dump2 = 0, *dump3 = 0, *dump4 = 0,
       *dump5 = 0;

static data_t *copy(data_t *cur)
{
    if (!cur || user((long)cur))
	return cur;
    if (cur->op == unknownident)
	return cur->list;
    *next = *cur;
    cur->op = unknownident;
    cur->list = next;
    return next++;
}

void gc()
{
    int i;
    long j;
    data_t *scan;
    clock_t start;

    stat_gc++;
    start = clock();
    next  = root.tab;
    stack = copy(stack);
    dump  = copy(dump);
    dump1 = copy(dump1);
    dump2 = copy(dump2);
    dump3 = copy(dump3);
    dump4 = copy(dump4);
    dump5 = copy(dump5);
    if (parms)
	*parms = copy(*parms);
    for (scan = root.tab; scan < next; scan++) {
	if (scan->op == typ_list)
	    scan->list = copy(scan->list);
	scan->next = copy(scan->next);
    }
    for (i = used() - 1; i > 0; i--)
	if ((j = peek(i)) == -typ_list) {
	    j = peek(--i);
	    poke(i, (long)copy((data_t *)j));
	}
    root.used = next - root.tab;
    gc_clock += clock() - start;
}

void reg(data_t **parm)
{
    parms = parm;
}

/*
    Allocate a number of nodes. If no nodes are available, start automatically
    the garbage collector. The number of nodes that are available after garbage
    collection determines whether the next time a larger or an equally large
    buffer is allocated.
*/
data_t *get(int num)
{
    data_t *temp;
    int prev, size;

/*
    If the current buffer is fully used, then the live nodes must be copied to
    the other buffer.
*/
    stat_kons += num;
    prev = root.prev;
    while (root.used + num > root.size) {
/*
    If the flag indicates that MORE nodes should be allocated, the number of
    nodes is adjusted such that it can satisfy allocation of NUM nodes.
*/
	if (root.flag == ALLOC_MORE) {
/*
    Initially, the sizes are 0. They must be set to 1. The new size is always
    set to the sum of the new size and the old size.
*/
	    size = root.size;
	    if ((root.size += root.prev) == 0)
		root.size = root.prev = 1;
	    else
		root.prev = size;
/*
    Setting the new size is repeated as often as necessary in order to make
    room for NUM nodes.
*/
	    while (root.used + num > root.size) {
		size = root.size;
		root.size += root.prev;
		root.prev = size;
	    }
	}
/*
    Now that it is known what must be the size of the new buffer, this buffer
    is allocated. The buffer is always allocated, even if swapping with the old
    buffer would be sufficient.
*/
	temp = root.old;
	root.old = root.tab;
	if (root.flag == DONT_ALLOC)
	    root.tab = temp;
	else
	    root.tab = calloc(root.size, sizeof(data_t));
/*
    The data is now copied from the old buffer to the new buffer. The code must
    not have any references to the data stack, because these references will be
    lost.
*/
	gc();
	if (root.flag != DONT_ALLOC)
	    free(temp);
/*
    Afterwards, the flag is filled that decides whether the next time a larger
    or an equally large buffer will be allocated.
*/
	if (root.used + num >= (root.size - prev))
	    root.flag = ALLOC_MORE;
	else if (root.flag == ALLOC_MORE)
	    root.flag = ALLOC_SAME;
	else
	    root.flag = DONT_ALLOC;
    }

/*
    Unless malloc failed, it is now time to return a node to the caller.
*/
    temp = &root.tab[root.used];
    root.used += num;
    parms = 0;
    return temp;
}

void mrep(long *size, long *prev, long *used)
{
    *size = root.size;
    *prev = root.prev;
    *used = root.used;
}
