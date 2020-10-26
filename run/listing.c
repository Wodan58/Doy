/*
    module  : listing.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <stdlib.h>
#include "listing.h"

FILE *listing = 0;

static char *name = 0;

void initlisting(char *str)
{
    name = str;
}

void openlisting()
{
    if (!listing && name)
	if ((listing = fopen(name, "w")) == NULL) {
	    fprintf(stderr, "%s (not open for writing)\n", name);
	    exit(EXIT_FAILURE);
	}
}

void exitlisting()
{
    if (listing)
	fclose(listing);
    listing = 0;
}
