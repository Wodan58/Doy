/*
    module  : token.h
    version : 1.2
    date    : 10/26/20
*/
typedef union value_t {
    long num;
    char *str;
    double dbl;
    long val;
} value_t;

extern int sym;
extern value_t val;

void ExpCh(void);
void ExpSpace(void);
void ExpNewLine(void);
void ExpString(void);
void getsym(void);
void ExpSet(void);
