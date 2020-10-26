/*
    module  : factor.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include "data.h"
#include "ident.h"
#include "token.h"
#include "error.h"
#include "local.h"
#include "factor.h"

static int list = 0;

/*
factor		    ::= atomic-symbol | boolean-constant
			| character-constant | integer-constant
			| float-constant | string-constant
			| "{" { character-constant | integer-constant } "}"
			| "[" term "]
*/
void readfactor()
{
    data_t *cur;

    switch (sym) {
    case '{' :
	ExpSet();
	/* continue */

    case typ_symbol  :
    case typ_logical :
    case typ_char    :
    case typ_integer :
    case typ_string  :
    case typ_float   :
	cur = get(1);
	cur->op = sym;
	cur->val = val.val;
	cur->next = stack;
	stack = cur;
	break;

    case '[' :
	list++;
	getsym();
	readterm();
	list--;
	if (sym != ']')
	    ExpError(RIGHT_BRACKET_EXPECTED);
	break;

    case def_end :
	if (list) {
	    cur = get(1);
	    cur->op = typ_symbol;
	    cur->num = sym_stop;
	    cur->next = stack;
	    stack = cur;
	    return;
	}
	/* continue */

    case def_module  :
    case def_private :
    case def_public  :
    case EOF :
    case ')' :
    case ';' :
    case ']' :
    case '}' :
	break;

    default :
	ExpError(INTERNAL_IN_READFACTOR);
	break;
    }  /* CASE */
}

static int endterm()
{
    if (list)
	return sym == ']' || sym == EOF;
    return sym == def_module || sym == def_private || sym == def_public ||
	   sym == def_end || sym == ')' || sym == ';' || sym == ']' ||
	   sym == EOF;
}

/*
term		    ::= { factor }
*/
void readterm()
{
    data_t *cur;

    cur = get(1);
    cur->op = typ_list;
    cur->list = 0;
    cur->next = stack;
    stack = cur;
    if (!endterm()) {
	readfactor();
	stack->next->list = stack;
	stack = stack->next;
	stack->list->next = 0;
	getsym();
	if (!endterm()) {
	    cur = get(1);
	    cur->op = typ_list;
	    cur->list = stack->list;
	    cur->next = dump;
	    dump = cur;
	    while (!endterm()) {
		readfactor();
		dump->list->next = stack;
		stack = stack->next;
		dump->list = dump->list->next;
		dump->list->next = 0;
		getsym();
	    }
	    dump = dump->next;
	}
    }
}
