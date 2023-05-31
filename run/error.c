/*
    module  : error.c
    version : 1.4
    date    : 07/08/22

	void Warning(int num, char *str)
	void Error(int num)
	void ExpError(int num)
	void ExecError(int num, char *op)
*/
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "error.h"

static char *messg[] = {
    "right parenthesis",		// ExpError: expected
    "valid start of scan expr",		// ExpError: illegal start of scan expr
    "fewer include files",		// ExpError: too many include files
    "\"A\" .. \"Z\"",			// ExpError: expected
    "\"=\"",				// ExpError: expected
    "unknown directive",		// Error:
    "radix not supported",		// Warning: exceeding alternative radix
    "internal error - selfreference",	// Error:
    "dynamic memory",			// ExpError: dynamic memory exhausted
    "internal error - circular",	// Error:
    "valid factor",			// ExpError: internal in readfactor
    "atomic symbol",			// ExpError: pass2: identifier expected
    "\"==\"",				// ExpError: pass2: == expected
    " (not open for reading)",		// Error:
    "string",				// ExpError:
    "character",			// ExpError:
    "definition",			// ExecError:
    "digit expected",			// Warning:
    "numeric in set",			// ExpError: numeric expected in set
    "']'",				// ExpError: ] expected
    "'(' not implemented",		// Warning: ( not implemented
    "overwriting inbuilt '%s'",		// Warning:
    "byte value",			// ExpError:
    "redefinition of '%s'",		// Warning:
    "%s"
};

void Warning(int num, char *str)
{
    point();
    fprintf(stderr, "\nwarning: ");
    fprintf(stderr, messg[num], str);
    fputc('\n', stderr);
}

void Error(int num)
{
    point();
    fprintf(stderr, "\nerror: %s\n", messg[num]);
    exit(1);
}

void ExpError(int num)
{
    point();
    fprintf(stderr, "\nerror: %s expected\n", messg[num]);
    exit(1);
}

void ExecError(int num, char *op)
{
    fflush(stdout);
    fprintf(stderr, "\nrun time error: %s needed for %s\n", messg[num], op);
}
