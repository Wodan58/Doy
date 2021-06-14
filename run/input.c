/*
    module  : input.c
    version : 1.5
    date    : 06/14/21

	void inp_init(void)
	void inp_exit(void)
	void point(void)
	void echonewline(int mode)
	void firstfile(char *str)
	void newfile(char *str)
	void echoline(void)
	int getch(void)
	void ungetch(int ch)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chars.h"
#include "error.h"
#include "listing.h"
#include "stack.h"
#include "input.h"

typedef struct files_t {
    FILE *file;
    char *name;
    int line;
} files_t;

int ch = 0, echoflag = 0, outlinelength = 0;

static int unget = 0;

static files_t inputs[MAXINP];
static FILE *yyin = 0;
static int line = 0, level = 0;

static char linebuf[MAXSTR];
static int leng = 0, cc = 0;

void inp_init()
{
    stk_init();
    inputs[0].file = yyin = stdin;
    inputs[0].name = strdup("stdin");
    inputs[0].line = line = 1;
}

void inp_exit()
{
    int i;

    for (i = 0; i < MAXINP; i++)
	if (inputs[i].name)
	    free(inputs[i].name);
}

/*
    At inputs[0] stdin and the line number of stdin are stored.
*/
void point()
{
    int i, ch;

    fflush(stdout);
    if (!line)
	return;
    if (outlinelength)
	fprintf(stderr, "\n");
    if (inputs[level].name)
	fprintf(stderr, "%s:\n", inputs[level].name);
    fprintf(stderr, "%4d\t", line);
    for (i = 0; i < cc; i++)
	fputc(linebuf[i], stderr);
    fprintf(stderr, "\n\t");
    for (i = 0; i < cc - 1; i++)
	if ((ch = linebuf[i]) < SPACE)
	    fputc(ch, stderr);
	else
	    fputc(SPACE, stderr);
    fprintf(stderr, "^\n");
}

void echonewline(int mode)
{
    if (echoflag && (leng || mode)) {
	fputc('\n', listing);
	leng = 0;
    }
}

/*
    The compiler calls this function to read from a file instead of from stdin.
    A subsequent file that is opened will be recorded in inputs[1].
    inputs[0] is the first file and on hitting EOF in that file ends
    compilation. The name is not filled, in case of stdin.
*/
void firstfile(char *str)
{
    inputs[0].file = yyin = freopen(str, "r", stdin);
    if (!yyin)
	Error(NOT_OPEN_FOR_READING);
    inputs[0].name = strdup(str);
}

void redirect(FILE *fp)
{
    if (inputs[level].file == fp)
	return;
    inputs[level].line = line;
    if (++level == MAXINP)
	ExpError(TOO_MANY_INCLUDE_FILES);
    inputs[level].file = yyin = fp;
    inputs[level].name = 0;
    inputs[level].line = line = 1;
}

void newfile(char *str)
{
    int length;
    char *name, *buf = 0, *ptr;

    inputs[level].line = line;
    if ((yyin = fopen(str, "r")) == 0) {
	if ((name = inputs[level].name) != 0) {
	    if ((ptr = strrchr(name, '/')) != 0) {
		length = ptr - name;
		if ((buf = malloc(length + strlen(str) + 2)) != 0) {
		    sprintf(buf, "%.*s/%s", length, name, str);
		    yyin = fopen(buf, "r");
		}
	    }
	}
    }
    if (!buf)
	buf = strdup(str);
    if (++level == MAXINP)
	ExpError(TOO_MANY_INCLUDE_FILES);
    inputs[level].file = yyin;
    inputs[level].line = line = 1;
    if (inputs[level].name)
	free(inputs[level].name);
    inputs[level].name = buf;
    echonewline(0);
    if (!yyin)
	Error(NOT_OPEN_FOR_READING);
}

void echoline()
{
    int i;

    if (echoflag > 2)		/* linenum */
	fprintf(listing, "%4d", line - 1);
    if (echoflag > 1)		/* tab */
	fputc('\t', listing);
    if (echoflag)
	for (i = 0; linebuf[i] != '\n'; i++)
	    fputc(linebuf[i], listing);
    fputc('\n', listing);
}

int getch()
{
    if (unget) {
	ch = unget;
	unget = 0;
	return ch;
    }
begin:
    if ((ch = fgetc(yyin)) == EOF) {
	if (!level)
	    return ch;
	fclose(yyin);
	yyin = inputs[--level].file;
	line = inputs[level].line;
	goto begin;
    }
    if (echoflag) {			/* echo */
	if (!leng) {
	    if (echoflag > 2)		/* linenum */
		fprintf(listing, "%4d", line);
	    if (echoflag > 1)		/* tab */
		fputc('\t', listing);
	}
	if (ch != ESCAPE || cc)
	    fputc(ch, listing);
	leng = 1;
    }
    if (ch == ESCAPE && !cc) {
	while ((ch = fgetc(yyin)) != EOF && ch != '\n')
	    if (cc < MAXSTR - 1)
		linebuf[cc++] = ch;
	linebuf[cc] = 0;
	system(linebuf);
    }
    if (cc < MAXSTR)
	linebuf[cc++] = ch;
    if (ch == '\n') {
	line++;
	leng = cc = 0;
    }
    return ch;
}

void ungetch(int ch)
{
    unget = ch;
}
