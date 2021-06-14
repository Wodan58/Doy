/*
    module  : input.h
    version : 1.3
    date    : 06/14/21
*/
#define MAXINP		  10

extern int ch, echoflag, outlinelength;

void inp_init(void);
void inp_exit(void);
void point(void);
void echonewline(int mode);
void firstfile(char *str);
void redirect(FILE *fp);
void newfile(char *str);
void echoline(void);
int getch(void);
void ungetch(int ch);
