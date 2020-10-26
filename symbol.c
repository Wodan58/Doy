/*
    module  : symbol.c
    version : 1.2
    date    : 10/26/20
*/
#include "array.h"
#include "symbol.h"

static array_t search, global;

/*
    sym_lookup - find a name in the symbol table; this uses a binary search
                 in the search table; the return value is the index in the
                 symbol table.
*/
int sym_lookup(char *name)
{
    int idx;
    symbol_t sym;
    search_t sch, *tmp;

/*
    search the name in the search table; a return value > 0 indicates that
    the name was found; a return value < 0 indicates that the name was not
    found.
*/
    if ((idx = search_line(&search, name)) > 0) {
        tmp = index_line(&search, idx);
        return tmp->value;
    }
    sym.name = sch.name = name;
    sym.value = sym.sym = sym.id = sym.used = sym.print = 0;
    sch.value = add_line(&global, -1, &sym);
    return add_line(&search, -idx, &sch);
}

/*
    sym_getsym - given an index in the symbol table, return a pointer to that
		 line; the pointer needs to be used immediately.
*/
symbol_t *sym_getsym(int idx)
{
    return index_line(&global, idx);
}

/*
    sym_loop - given an index in the symbol table, return a pointer to that
	       line; the pointer needs to be used immediately.
*/
symbol_t *sym_loop(int idx, long *num)
{
    search_t *tmp;

    if ((tmp = index_line(&search, idx)) == 0)
        return 0;
    return index_line(&global, *num = tmp->value);
}

/*
    sym_init - keywords and builtins are added to the symbol table.
*/
void sym_init()
{
    init_array(&search, sizeof(search_t));
    init_array(&global, sizeof(symbol_t));
    sym_lookup("");
}
