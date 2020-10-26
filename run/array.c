/*
    module  : array.c
    version : 1.2
    date    : 10/26/20

	void init_array(array_t *arr, int width)
	int last_index(array_t *arr)
	void *index_line(array_t *arr, int lineno)
	int remove_line(array_t *arr, int lineno)
	int add_line(array_t *arr, int lineno, void *line)
	int search_line(array_t *arr, void *key)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"

/*
    Initialise the dynamic array.
*/
void init_array(array_t *arr, int width)
{
    arr->count = 0;
    if (!arr->width) {
	arr->width = width;
	arr->current = 0;
	arr->previous = 0;
	arr->size = 0;
	arr->table = 0;
    }
}

/*
    Provide the highest index.
*/
int last_index(array_t *arr)
{
    return arr->count - 1;
}

/*
    Provide a line from the table.
    Valid line numbers are 0 .. count-1.
*/
void *index_line(array_t *arr, int lineno)
{
    if (lineno == -1)
	lineno = arr->count - 1;
    else if (lineno < 0 || lineno >= arr->count)
	return 0;
    return arr->table + lineno * arr->width;
}

/*
    Remove a line from the table. Any data that was allocated in that line
    is not released.
*/
int remove_line(array_t *arr, int lineno)
{
    int cnt;
    char *dst;

    if (lineno == -1) {
	if (arr->count)
	    arr->count--;
	return 0;
    } else if (lineno < 0 || lineno >= arr->count)
	return -1;
    if (--arr->count > lineno) {
	cnt = (arr->count - lineno) * arr->width;
	dst = arr->table + lineno * arr->width;
	memcpy(dst, dst + arr->width, cnt);
    }
    return 0;
}

/*
    Add a line to the table. If necessary the table is extended with a line.
    The index where the line was added is returned.
*/
int add_line(array_t *arr, int lineno, void *line)
{
    char *dst;
    int cnt, aant;

    if (lineno == -1)
	lineno = arr->count;
    else if (lineno < 0 || lineno > arr->count)
	return -1;
    cnt = (arr->count + 1) * arr->width;
    if (arr->size < cnt) {
	if (!arr->current)
	    arr->current = arr->previous = 1;
	else {
	    aant = arr->current;
	    arr->current += arr->previous;
	    arr->previous = aant;
	    cnt = arr->current * arr->width;
	}
	if ((arr->table = realloc(arr->table, cnt)) == 0)
	    return -1;
	arr->size = cnt;
    }
    dst = arr->table + lineno * arr->width;
    if (arr->count > lineno) {
	cnt = (arr->count - lineno) * arr->width;
	memmove(dst + arr->width, dst, cnt);
    }
    memcpy(dst, line, arr->width);
    return arr->count++;
}

/*
    Find a line in the table. The key of the line is a pointer to an allocated
    string at the start of the line.
*/
int search_line(array_t *arr, void *key)
{
    char *ptr;
    int low, mid, high, cmp;

    low = 0;			/* first line */
    high = arr->count - 1;	/* last line */
    while (low <= high) {
	mid = low + (high - low) / 2;
	memcpy(&ptr, &arr->table[mid * arr->width], sizeof(ptr));
	if ((cmp = strcmp(key, ptr)) == 0)
	    return mid;
	if (cmp < 0)
	    high = mid - 1;
	else
	    low = mid + 1;
    }
    return -low;
}
