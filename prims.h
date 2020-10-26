/*
    module  : prims.h
    version : 1.2
    date    : 10/26/20
*/
enum {
    PLAIN,
    HTML,
    LATEX
};

void make_manual(int style);
void manual_list(void);
void helpdetail(void);
