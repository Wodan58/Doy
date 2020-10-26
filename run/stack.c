/*
    module  : stack.c
    version : 1.1
    date    : 10/26/20
*/
#include <stdlib.h>
#include "stack.h"

#define MAX_STACK	1000000		// 8 MB
#define MAGIC_VAL	0xCAFEDADADEADBEEF

static long stack_bottom;	// cold end of the stack, in high memory

/*
    A large portion of the stack is filled with a magic unsigned value.
*/
static void color_stack(int block)
{
    int i;
    unsigned long *ptr = alloca(block * sizeof(char *));

    for (i = block - 1; i > 0; i--)
	ptr[i] = MAGIC_VAL;
}

/*
    The address of the first unsigned without the magic value is reported.
*/
static long check_stack(int block)
{
    int i;
    unsigned long *ptr = alloca(block * sizeof(char *));

    for (i = 0; i < block; i++)
	if (ptr[i] == MAGIC_VAL)
	    break;
    for (; i < block; i++)
	if (ptr[i] != MAGIC_VAL)
	    break;
    return (long)&ptr[i];
}

void stk_init()
{
    char dummy;

    stack_bottom = (long)&dummy;
    color_stack(MAX_STACK);
}

void srep(long *size, long *prev, long *used)
{
    *size = MAX_STACK * sizeof(char *);
    *prev = (long)stack_bottom;
    *used = (stack_bottom - check_stack(MAX_STACK)) * sizeof(char *);
}
