/*
    module  : flex.c
    version : 1.2
    date    : 10/26/20

	void flex_init()
	void flex_exit()
	char *flex_get()
	void flex_add(int ch)
*/
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "flex.h"

/*
    The purpose of flex is to keep a string; the string can become arbitrarily
    large. Only one string needs to be kept.
*/
static array_t flex;

/*
    flex_init - the string is initialised; the length of a line in the table is
		1 character. After adding a character a \0 is added.
*/
void flex_init()
{
    init_array(&flex, sizeof(char));
    add_line(&flex, -1, "");
    remove_line(&flex, -1);
}

void flex_exit()
{
    if (flex.table)
	free(flex.table);
}

/*
    flex_get - return a pointer to the table. The pointer must be used
	       immediately.
*/
char *flex_get()
{
    return flex.table;
}

/*
    flex_add - add a character to a string. The string is always extenden with
	       an ending \0 byte.
*/
void flex_add(int ch)
{
    char str[1];

    str[0] = ch;
    add_line(&flex, -1, str);
    add_line(&flex, -1, "");
    remove_line(&flex, -1);
}
