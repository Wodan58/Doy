/*
    module  : writestr.c
    version : 1.2
    date    : 10/26/20

	void writestr(char *str)
*/
#include <stdio.h>
#include <ctype.h>
#include "boole.h"
#include "writestr.h"

void writestr(char *str)
{
    int quote = FALSE;

    for ( ; *str; str++)
	if (isprint((int)*str) && *str != '\'') {
	    if (!quote) {
		quote = TRUE;
		putchar('\'');
	    }
	    putchar(*str);
	} else {
	    if (quote) {
		quote = FALSE;
		printf("',");
	    }
	    printf("%d,", *str);
	}
    if (quote)
	printf("',");
    printf("0\n");
}
