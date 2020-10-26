/*
    module  : memory.c
    version : 1.2
    date    : 10/26/20
*/
#include "defs.h"
#include "array.h"
#include "memory.h"

static array_t memory;

/*
    mem_init - the memory table is initialised; the node with index 0 is not
	       used.
*/
void mem_init()
{
    memory_t node;

    init_array(&memory, sizeof(memory_t));
    node.val = node.nxt = node.op = node.marked = 0;
    mem_put(&node);
}

/*
    mem_get - give an index in the memory table, return a pointer to that line;
	      the pointer must be used immediately.
*/
memory_t *mem_get(memrange idx)
{
    return index_line(&memory, idx);
}

/*
    mem_put - allocate space for a node and fill the node.
*/
memrange mem_put(memory_t *node)
{
    return add_line(&memory, -1, node);
}
