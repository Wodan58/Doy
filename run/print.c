/*
    module  : print.c
    version : 1.2
    date    : 10/26/20

	void newline(FILE *fp)
	void nl(void)
	void putch(int ch, FILE *fp)
	void newspace(FILE *fp)
	void printfactor(data_t *cur, FILE *fp)
	void printterm(data_t *head, FILE *fp)
	void printstack(data_t *root, FILE *fp)
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "chars.h"
#include "boole.h"
#include "data.h"
#include "ident.h"
#include "local.h"
#include "set32.h"
#include "error.h"
#include "lookup.h"
#include "input.h"
#include "print.h"

#define MAX_LINE	60

static int sp = 0;

void newline(FILE *fp)
{
    fputc('\n', fp);
    outlinelength = 0;
    sp = TRUE;
}

void nl(void)
{
    if (outlinelength > 0)
	newline(stdout);
}

void putch(int ch, FILE *fp)
{
    echonewline();
    if (ch == '\n' || (isspace(ch) && outlinelength >= MAX_LINE))
	newline(fp);
    else {
	fputc(ch, fp);
	outlinelength++;
    }
    sp = isspace(ch);
}

void newspace(FILE *fp)
{
    if (!outlinelength)
	sp = TRUE;
    if (!sp)
	putch(SPACE, fp);
}

static void putstr(char *str, FILE *fp)
{
    int leng;

    if (!str)
	return;
    if ((leng = strlen(str)) == 0)
	return;
    fprintf(fp, "%s", str);
    outlinelength += leng;
    if (str[leng - 1] == '\n')
	outlinelength = 0;
    sp = isspace((int)str[leng - 1]);
}

static int unescape(int ch)
{
    switch (ch) {
    case '\b' :
	return 'b';

    case '\t' :
	return 't';

    case '\n' :
	return 'n';

    case '\v' :
	return 'v';

    case '\f' :
	return 'f';

    case '\r' :
	return 'r';

    case '"'  :
    case '\'' :
    case '\\' :
	return ch;

    default   :
	return 0;
    }
}

static void printstr(char *str, FILE *fp)
{
    int ch;
    char buf[10];

    fputc('"', fp);
    for ( ; (ch = *str) != 0; str++) {
	if (ch < SPACE || ch == '"' || ch == '\\' || ch == DELETE) {
	    fputc('\\', fp);
	    outlinelength++;
	    if ((ch = unescape(ch)) == 0) {
		sprintf(buf, "%03d", *str);
		fputc(buf[0], fp);
		fputc(buf[1], fp);
		ch = buf[2];
		outlinelength += 2;
	    }
	}
	fputc(ch, fp);
	outlinelength++;
    }
    fputc('"', fp);
    sp = FALSE;
    outlinelength += 2;
}

void printfactor(data_t *cur, FILE *fp)
{
    int i, j;
    char str[MAXSTR];

    if (!cur)
	return;
    switch (cur->op) {
    case typ_logical :
	if (cur->num == 1)
	    putstr(lookup2(sym_true), fp);
	else
	    putstr(lookup2(sym_false), fp);
	break;

    case typ_char :
	if (isspace(cur->num))
	    sprintf(str, "%c", (int)cur->num);
	else if (isprint(cur->num))
	    sprintf(str, "'%c", (int)cur->num);
	else
	    sprintf(str, "'\\%03d", (int)cur->num);
	putstr(str, fp);
	break;

    case typ_integer :
	sprintf(str, "%ld", (long)cur->num);
	putstr(str, fp);
	break;

    case typ_set :
	putch('{', fp);
	j = cur->num;
	for (i = 0; i < SETSIZE; i++)
	    if (tst_bit(j, i)) {
		sprintf(str, "%d", i);
		putstr(str, fp);
		if ((j = del_bit(j, i)) != 0)
		    putch(SPACE, fp);
	    }
	putch('}', fp);
	break;

    case typ_string :
	if (cur->num < userindex)
	    printstr(lookup2(cur->num), fp);
	else
	    printstr(cur->str, fp);
	break;

    case typ_list :
	putch('[', fp);
	printterm(cur->list, fp);
	putch(']', fp);
	break;

    case typ_float :
	sprintf(str, "%f", cur->dbl);
	putstr(str, fp);
	break;

    case typ_file :
	sprintf(str, "%lx", (long)cur->num);
	putstr(str, fp);
	break;

    case lib_:
    case typ_symbol :
    case typ_function :
	if (cur->num < userindex)
	    putstr(lookup2(cur->num), fp);
	else
	    putstr(cur->str, fp);
	break;

    default :
	ExpError(INTERNAL_IN_READFACTOR);
	break;
    }
}

void printterm(data_t *root, FILE *fp)
{
    data_t *cur;

    for (cur = root; cur; cur = cur->next) {
	if (cur != root)
	    newspace(fp);
	printfactor(cur, fp);
    }
}

void printstack(data_t *root, FILE *fp)
{
    if (!root)
	return;
    printstack(root->next, fp);
    newspace(fp);
    printfactor(root, fp);
}
