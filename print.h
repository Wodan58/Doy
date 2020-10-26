/*
    module  : print.h
    version : 1.2
    date    : 10/26/20
*/
void newline(FILE *fp);
void nl(void);
void putch(int ch, FILE *fp);
void newspace(FILE *fp);
void printfactor(data_t *root, FILE *fp);
void printterm(data_t *root, FILE *fp);
void printstack(data_t *root, FILE *fp);
