/*
    module  : symbol.h
    version : 1.2
    date    : 10/26/20
*/

/*
    symbol_t contains the actual value of a symbol.
*/
typedef struct symbol_t {
    char *name;
    long value;
    unsigned short sym, id;
    unsigned char used, print, level, prime;
} symbol_t;

/*
    search_t offers a binary search into the symbol table.
*/
typedef struct search_t {
    char *name;
    long value;
} search_t;

extern search_t joy_table[], end_table[];

int sym_lookup(char *name);
symbol_t *sym_getsym(int idx);
symbol_t *sym_loop(int i, long *j);
void sym_init(void);

void sym_exit(void);
void sym_section(int mode);
int sym_default(void);
