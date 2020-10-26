/*
    module  : nodes.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "chars.h"
#include "proc.h"
#include "symbol.h"
#include "print.h"
#include "nodes.h"

static int lookup4(long val)
{
    search_t *psym;

    for (psym = joy_table; psym < end_table; psym++)
	if (val == psym->value)
	    return psym - joy_table;
    return -1;
}

static int Adr2Type(long adr)
{
    if (adr == (long)is_logical)
	return typ_logical;
    if (adr == (long)is_char)
	return typ_char;
    if (adr == (long)is_integer)
	return typ_integer;
    if (adr == (long)is_set)
	return typ_set;
    if (adr == (long)is_set)
	return typ_set;
    if (adr == (long)is_string)
	return typ_string;
    if (adr == (long)is_list)
	return typ_list;
    if (adr == (long)is_float)
	return typ_float;
    if (adr == (long)is_file)
	return typ_file;
    if (adr == (long)is_user)
	return typ_symbol;
    if (adr == (long)is_user)
	return typ_symbol;
    return typ_function;
}

/*
     8 00000000 BF2E000000              L1	mov	rdi,46
    10 00000005 E8(00000000)            	call	is_integer
    11 0000000A 48BF-                   L2	mov	rdi,L3
    11 0000000C [0000000000000000] 
    47 0000004B C3                      L0	ret
*/
int readcode(node_t *cur, data_t *node)
{
    long adr;

    node->op = lib_;
    if (cur->op == 0xE8) {
	adr = (long)(&cur->op + (int)cur->val + 5);
	if ((node->num = lookup4(adr)) != -1)
	    node->op = typ_symbol;
	return 5;
    }
    if (cur->op == 0xBF) {
	node->op = typ_integer;
	node->num = (int)cur->val;
	return 10;
    }
    if (cur->op == 0x48) {
	cur = (node_t *)((char *)cur + 1);	// point to BF
	node->num = cur->val;
	adr = (long)(&cur->call + (int)cur->adr + 5);
	node->op = Adr2Type(adr);
	return 15;
    }
    return 1;
}

void printprogram(unsigned char *code, FILE *fp)
{
    data_t cur;

    while (*code != 0xC3) {
	code += readcode((node_t *)code, &cur);
	printfactor(&cur, fp);
	if (*code != 0xC3)
	    putch(SPACE, fp);
    }
}
