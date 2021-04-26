/*
    module  : strings.c
    version : 1.3
    date    : 04/24/21

	void str_init()
	void str_exit()
	char *str_get(int idx)
	int str_add(char *str)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"
#include "strings.h"

static array_t strings;

/*
    str_init - the string table is initialised; the node at index 0 is not
	       used.
*/
void str_init()
{
    init_array(&strings, sizeof(my_string_t));
    str_add("");
}

void str_exit()
{
    if (strings.table)
	free(strings.table);
}

/*
    str_get - given an index in the strings table, return a pointer to that
	      line; the pointer must be used immediately.
*/
char *str_get(int idx)
{
    my_string_t *pstr;

    if ((pstr = index_line(&strings, idx)) == 0)
	return 0;
    return pstr->str;
}

/*
    str_add - allocate space for a node and fill the node.
*/
int str_add(char *str)
{
    my_string_t node;

    node.str = strdup(str);
    return add_line(&strings, -1, &node);
}
