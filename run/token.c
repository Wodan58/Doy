/*
    module  : token.c
    version : 1.2
    date    : 10/26/20

	void ExpCh(void)
	void ExpSpace(void)
	void ExpNewLine(void)
	void ExpString(void)
	void getsym(void)
	void ExpSet(void)

	SYM		VAL
	---		---

	MODULE
	PRIVATE
	PUBLIC
	EQUAL

	typ_symbol	val.num
	typ_logical	val.num		false, true
	typ_char	val.num
	typ_integer     val.num		maxint
	typ_set		val.num		{
	typ_string      val.str
	typ_list			cycle.c : [
	typ_float	val.dbl
	typ_file			dolib.c : stdin, stdout, stderr

	EOF
	(
	)
	.
	;
	[
	]
	{
	}
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "defs.h"
#include "input.h"
#include "flex.h"
#include "chars.h"
#include "boole.h"
#include "error.h"
#include "value.h"
#include "ident.h"
#include "lookup.h"
#include "set32.h"
#include "listing.h"
#include "token.h"

value_t val;
int sym = 0;

void ExpCh()
{
    if (!ch)
	flex_init();
    ch = getch();
}

void ExpSpace()
{
    while (ch >= 0 && ch <= SPACE)
	ExpCh();
}

void ExpNewLine()
{
    while (ch != '\n' && ch != EOF)
	ExpCh();
}

static int ExpComment()
{
    ExpCh();			// to get past (
    if (ch == '*') {
	ExpCh();		// to get past *
	do {
	    while (ch != '*' && ch != EOF)
		ExpCh();
	    if (ch == '*')
		ExpCh();	// to get past *
	} while (ch != ')' && ch != EOF);
	if (ch == ')')
	    ExpCh();		// to get past )
	return TRUE;
    }
    Warning(PARENTHESIS_NOT_IMPLEMENTED, 0);
    sym = '(';
    return FALSE;
}

/*
reserved-character  ::= "(" | ")" | "." | ";" | "[" | "]" | "{" | "}"
*/
static void ExpReserved()
{
    if (ch == ')')
	Warning(PARENTHESIS_NOT_IMPLEMENTED, 0);
    if ((sym = ch) != EOF)
	ExpCh();		// to get past ().;[]{}
    if (sym == '.')
	sym = def_end;
}

static int ExpDigit()
{
    ExpCh();
    if (!isdigit(ch)) {
	Warning(DIGIT_EXPECTED, 0);
	return FALSE;
    }
    return TRUE;
}

/*
escaped-character   ::= "\b" | "\t" | "\n" | "\f" | "\r" | "\"" | "'" | "\ddd"
*/
static void ExpEscapedCharacter()
{
    if (isdigit(ch)) {
	val.num = ch - '0';
	if (ExpDigit()) {
	    val.num *= 10;
	    val.num += ch - '0';
	    if (ExpDigit()) {
		val.num *= 10;
		val.num += ch - '0';
	    }
	}
	if (val.num > MAXCHR)
	    ExpError(BYTE_VALUE_EXPECTED);
    } else {
	switch (ch) {
	case 'b'  :
	    val.num = '\b';
	    break;

	case 't'  :
	    val.num = '\t';
	    break;

	case 'n'  :
	    val.num = '\n';
	    break;

	case 'v'  :
	    val.num = '\v';
	    break;

	case 'f'  :
	    val.num = '\f';
	    break;

	case 'r'  :
	    val.num = '\r';
	    break;

	case '"'  :
	case '\'' :
	case '\\' :
	    val.num = ch;
	    break;

	default   :		// space, uppercase
#if 0
	    val.num = ch;
#endif
	    ungetch(ch);
	    val.num = value();
	    break;
	}
    }
    ExpCh();
}

/*
ordinary-character  ::= any character, except "\"
*/
static void ExpOrdinaryCharacter()
{
    val.num = ch;
    ExpCh();
}

/*
character-constant  ::= "'" ( escaped-character | ordinary-character )
*/
static void ExpCharacter()
{
    ExpCh();			// to get past '
    if (ch == '\\') {
	ExpCh();		// to get past escape
	ExpEscapedCharacter();
    } else
	ExpOrdinaryCharacter();
#if 0
    if (ch == '\'')
	ExpCh();
#endif
    sym = typ_char;
}

/*
string-constant     ::= '"' { escaped-character | ordinary-character } '"'
*/
void ExpString()
{
    ExpCh();			// to get past "
    flex_init();
    while (ch != '"') {
	if (ch == '\\') {
	    ExpCh();		// to get past escape
	    ExpEscapedCharacter();
	} else
	    ExpOrdinaryCharacter();
	flex_add(val.num);
    }
    val.str = strdup(flex_get());
    ExpCh();			// to get past "
    sym = typ_string;
}

static void ExpRestSymbol()
{
    do {
	flex_add(ch);
	ExpCh();
    } while (isalnum(ch) || ch == '-' || ch == '=' || ch == '_' || ch == '>');
    if (ch == '.') {
	ExpCh();		// to get past .
	if (ch == EOF || isspace(ch) || strchr("\"#'().0123456789;[]{}", ch)) {
	    ungetch(ch);
	    ch = '.';
	} else {
	    flex_add('.');
	    ExpRestSymbol();
	}
    }
}

/*
atomic-symbol       ::= any printing character which is not a reserved
			character or a digit or the single or double quote
			character (or the comment-character)
			{ letter | digit | "-" | "=" | "_" }
comment-character   ::= "#"
*/
static void ExpSymbol()
{
    int num;

    if (ch == EOF || isspace(ch) || strchr("\"#'().;[]{}", ch))
	goto einde;
    ExpRestSymbol();
einde:
/*
reserved-word       ::= "==" | "MODULE" | "PRIVATE" | "PUBLIC" | "END"
			| "HIDE" | "IN" | "DEFINE" | "LIBRA"
*/
    sym = lib_;
    num = lookup1(flex_get());
    if (writelisting > 4)
	fprintf(listing, "lookup : %s at %ld\n", flex_get(), val.num);
    if (sym == lib_) {
	switch (num) {
	case false_  :
	    val.num = FALSE;
	    sym = typ_logical;
	    break;

	case true_   :
	    val.num = TRUE;
	    sym = typ_logical;
	    break;

	case maxint_ :
	    val.num = MAXINT;
	    sym = typ_integer;
	    break;

	case -1 :
	    val.str = strdup(flex_get());
	    /* continue */

	default :
	    sym = typ_symbol;
	    break;
	}
    }
}

static int ExpDirective()
{
    flex_init();
    flex_add(ch);
    ExpCh();
    if (isupper(ch)) {
	ExpSymbol();
	directive();
	return TRUE;
    }
    ExpSymbol();
    return FALSE;
}

/*
integer-constant    ::= [ "-" ] ( "0" .. "9" ) { "0" .. "9" }
*/
static void ExpInteger()
{
    flex_add(ch);
    if (ch != '0')
	while (ExpCh(), isdigit(ch))
	    flex_add(ch);
    else {
	ExpCh();
	if (ch == 'x' || ch == 'X')
	    do {
		flex_add(ch);
		ExpCh();
	    } while (isxdigit(ch));
	else
	    while (ch >= '0' && ch <= '7') {
		flex_add(ch);
		ExpCh();
	    }
    }
}

static int ExpFloat()
{
    if (ch == '.') {
	ExpCh();		// to get past .
	if (!isdigit(ch)) {
	    ungetch(ch);
	    ch = '.';
	    return FALSE;
	}
	flex_add('.');
	do {
	    flex_add(ch);
	    ExpCh();
	} while (isdigit(ch));
    }
    if (ch == 'e' || ch == 'E') {
	flex_add(ch);
	ExpCh();		// to get past e or E
	if (ch == '+' || ch == '-') {
	    flex_add(ch);
	    ExpCh();		// to get past + or -
	}
	while (isdigit(ch)) {
	    flex_add(ch);
	    ExpCh();
	}
    }
    return TRUE;
}

static void ExpNumber()
{
    flex_init();
    if (ch == '-') {
	flex_add(ch);
	ExpCh();		// to get past -
	if (!isdigit(ch)) {
	    ExpSymbol();
	    return;
	}
    }
    ExpInteger();
    if ((ch == '.' || ch == 'e' || ch == 'E') && ExpFloat()) {
	val.dbl = atof(flex_get());
	sym = typ_float;
    } else {
	val.num = strtol(flex_get(), 0, 0);
	sym = typ_integer;
    }
}

static void ExpRadixNumber()
{
    int num;

    ExpCh();
    if (!isdigit(ch) && !isupper(ch)) {
	flex_init();
	flex_add('&');
	ExpSymbol();
	return;
    }
    val.num = 0;
    do {
	num = ch;
	if (isdigit(num))
	    num -= '0';
	else {
	    num -= 'A';
	    num += 10;
	}
	if (num >= radix)
	    Warning(EXCEEDING_ALTERNATIVE_RADIX, 0);
	val.num *= radix;
	val.num += num;
	ExpCh();
    } while (isdigit(ch) || isupper(ch));
    sym = typ_integer;
}

/*
token		    ::= reserved-character | character-constant
			| string-constant | integer-constant
			| float-constant | reserved-word
			| atomic-symbol
*/
void getsym()
{
begin:
    memset(&val, 0, sizeof(val));
    ExpSpace();
    switch (ch) {
    case '"' :
	ExpString();
	break;

    case '#' :
	ExpNewLine();
	goto begin;

    case '%' :
	if (ExpDirective())
	    goto begin;
	break;

    case '&' :
	ExpRadixNumber();
	break;

    case '\'' :
	ExpCharacter();
	break;

    case '(' :
	if (ExpComment())
	    goto begin;
	break;

    case EOF :
    case ')' :
    case '.' :
    case ';' :
    case '[' :
    case ']' :
    case '{' :
    case '}' :
	ExpReserved();
	break;

    case '-' :
    case '0' :
    case '1' :
    case '2' :
    case '3' :
    case '4' :
    case '5' :
    case '6' :
    case '7' :
    case '8' :
    case '9' :
	ExpNumber();
	break;

    default  :
	flex_init();
	ExpSymbol();
	break;
    }
}

static void ExpCharacterInteger()
{
    getsym();
    switch (sym) {
    case typ_char :
    case typ_integer :
    case '}' :
	break;

    default :
	ExpError(NUMERIC_EXPECTED_IN_SET);
	break;
    }
}

void ExpSet()
{
    int set = 0;

    do {
	ExpCharacterInteger();
	if (sym != '}')
	    set = set_bit(set, val.num);
    } while (sym != '}');
    val.num = set;
    sym = typ_set;
}
