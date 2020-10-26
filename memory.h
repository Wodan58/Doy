/*
    module  : memory.h
    version : 1.2
    date    : 10/26/20
*/
typedef short memrange;

typedef struct memory_t {
    long val;
    memrange nxt;
    unsigned char op;	/* R.W. was: standardident */
    unsigned char marked;
} memory_t;

void mem_init(void);
memory_t *mem_get(memrange idx);
memrange mem_put(memory_t *node);
