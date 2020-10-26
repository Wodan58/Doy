/*
    module  : value.c
    version : 1.2
    date    : 10/26/20

	int value(void)
	void directive(void)
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "input.h"
#include "token.h"
#include "ident.h"
#include "error.h"
#include "lookup.h"
#include "listing.h"
#include "value.h"

int writelisting = 0, statistics = 0, radix = 0, trace = 0;

static int variable['Z' - 'A' + 1];

int value()
{
    int rv = 0;

    ExpCh();
    ExpSpace();
    if (ch == '\'' || isdigit(ch)) {
	getsym();
	switch (sym) {
	case typ_logical :
	case typ_char    :
	case typ_integer :
	    rv = val.num;
	    break;

	case typ_float :
	    rv = (int)val.dbl;
	    break;

	default :
	    rv = ch;
	}
	goto einde;
    }
    if (isupper(ch)) {
	rv = variable[ch - 'A'];
	getsym();
	goto einde;
    }
    switch (ch) {
    case '(' :
	rv = value();
	ExpSpace();
	if (ch == ')')
	    ExpCh();
	else
	    ExpError(RIGHT_PARENTHESIS_EXPECTED);
	break;

    case '*' :
	rv = value() * value();
	break;

    case '+' :
	rv = value() + value();
	break;

    case '-' :
	rv = value();
	rv -= value();
	break;

    case '/' :
	rv = value();
	rv /= value();
	break;

    case '<' :
	rv = value();
	rv = rv < value();
	break;

    case '=' :
	rv = value() == value();
	break;

    case '>' :
	rv = value();
	rv = rv > value();
	break;

    case '?' :
	scanf("%d", &rv);
	break;

    default :
	ExpError(ILLEGAL_START_OF_SCAN_EXPR);
    }
einde:
    return rv;
}

static void puteoln()
{
    do {
	ExpCh();
	fputc(ch, stderr);
    } while (ch != '\n');
}

void directive()
{
    int rv = 'A';

    switch (sym) {
    case dir_if :
	if ((rv = value()) == 0)
	    ExpNewLine();
	break;

    case dir_include :
	ExpSpace();
	if (ch == '"') {
	    ExpString();
	    newfile(val.str);
	    free(val.str);
	} else
	    ExpError(STRING);
	break;

    case dir_listing :
	rv = echoflag;
	echoflag = value();
	if (!rv && echoflag) {
	    openlisting();
	    echoline();
	}
	break;

    case dir_put :
	puteoln();
	break;

    case dir_radix :
	radix = value();
	break;

    case dir_set :
	getsym();
	if (sym == typ_char || sym == typ_symbol) {
	    rv = sym == typ_char ? val.num : *lookup2(val.num);
	    if (rv < 'A' || rv > 'Z')
		ExpError(A_Z_EXPECTED);
	    getsym();
	    if (sym == typ_symbol && !strcmp(lookup2(val.num), "="))
		variable[rv - 'A'] = value();
	    else
		ExpError(IS_EXPECTED);
	} else
	    ExpError(CHARACTER);
	break;

    case dir_statistics :
	statistics = value();
	break;

    case dir_trace :
	rv = writelisting;
	writelisting = value();
	if (!rv && writelisting)
	    openlisting();
	break;

    default :
	Error(UNKNOWN_DIRECTIVE);
	break;
    }
    ExpCh();
}
