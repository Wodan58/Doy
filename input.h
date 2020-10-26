/*
    module  : input.h
    version : 1.2
    date    : 10/26/20
*/
#define MAXINP		  10

extern int ch, echoflag, outlinelength;

void inp_init(void);
void inp_exit(void);
void point(void);
void echonewline(void);
void firstfile(char *str);
void redirect(FILE *fp);
void newfile(char *str);
void echoline(void);
int getch(void);
void ungetch(int ch);
