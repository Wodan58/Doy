/*
    module  : stack.c
    version : 1.2
    date    : 02/22/21
*/
#include <stdlib.h>
#include "stack.h"

#define MAX_STACK	1000000		// 8 MB
#define MAGIC_VAL	0xCAFEDADADEADBEEF

static unsigned long *stack_top;	// hot end of the stack, in low memory

/*
    A large portion of the stack is filled with a magic unsigned value.
*/
static void stk_color(int block)
{
    int i;

    stack_top = alloca(block * sizeof(void *));
    for (i = block - 1; i > 0; i--)
	stack_top[i] = MAGIC_VAL;
}

/*
    The portion of the stack that has been used is reported.
*/
static int stk_used(int block)
{
    int i;

    stack_top = alloca(block * sizeof(void *));
    for (i = 0; i < block; i++)
	if (stack_top[i] == MAGIC_VAL)
	    break;
    for (; i < block; i++)
	if (stack_top[i] != MAGIC_VAL)
	    break;
    return block - i;
}

/*
    Initialize the hardware stack.
*/
void stk_init()
{
    stk_color(MAX_STACK);
}

/*
    Report size and used of the hardware stack.
*/
void srep(long *size, long *prev, long *used)
{
    *size = MAX_STACK * sizeof(void *);
    *prev = 0;
    *used = stk_used(MAX_STACK) * sizeof(void *);
}
