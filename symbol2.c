/*
    module  : symbol2.c
    version : 1.2
    date    : 10/26/20

	void sym_init(void)
	void sym_exit(void)
	int sym_lookup(char *name, int add)
	symbol_t *sym_getsym(int idx)
	symbol_t *sym_loop(int i, long *j)
	void sym_section(int mode)
	int sym_default(void)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"
#include "ident.h"
#include "symbol.h"

static char *module = 0;
static array_t search, global, locals;
static int section = 0, prev_section = 0, level = 0;

/*
    sym_init - keywords and builtins are added to the symbol table.
*/
void sym_init()
{
    section = prev_section = def_equal;
    init_array(&search, sizeof(search_t));
    init_array(&global, sizeof(symbol_t));
    init_array(&locals, sizeof(search_t));
    sym_lookup("");
}

void sym_exit()
{
    int i;
    symbol_t *psym;

    for (i = 0; (psym = sym_getsym(i)) != 0; i++)
	free(psym->name);
    if (module) {
	free(module);
	module = 0;
    }
    if (locals.table)
	free(locals.table);
    if (global.table)
	free(global.table);
    if (search.table)
	free(search.table);
}

/*
    Add a symbol to the global symbol table.
*/
static int sym_addsym(char *name, int nivo)
{
    symbol_t sym;

    sym.name = name;
    sym.level = nivo;
    sym.value = sym.sym = sym.id = sym.prime = sym.used = sym.print = 0;
    return add_line(&global, -1, &sym);
}

/*
    sym_lookup - search a name in the symbol table; this is done through binary
		 search in the search table or a linear search in the local
		 table; the return value is an index in the symbol table.

    A symbol is searched after an identifier has been read.
    An identifier can be everything, bu a number of characters are excepted:
    ( ) . ; [ ] { }
    If one of the words MODULE, PRIVATE, PUBLIC, ==, END is found (or a
    synonym thereof) no further lookup is needed. These keywords cannot be
    redefined.
*/
int sym_lookup(char *name)
{
    char *str = 0;
    symbol_t *psym;
    search_t sch, *psch;
    int g_idx = 0, l_idx = 0, value = 0, size;

    if (!*name)
	goto store;
    if (module) {
	size = strlen(module) + strlen(name) + 2;
	str = malloc(size);
	sprintf(str, "%s.%s", module, name);
    }

/*
    Search a name in the search table; a return value >= 0 indicates that the
    name has been found; a return value <= 0 indicates that the name was not
    found. The absolute return value points to the index where the name was
    found or should be located. in case of a 0 return value, it is uncertain
    whether the name was found or not; that is why initially an empty string
    is searched and added; an empty string will never be searched and thus
    the problem does not exist anymore.
*/
    if ((g_idx = search_line(&search, name)) > 0) {
	psch = index_line(&search, g_idx);
	psym = sym_getsym(value = psch->value);
	if (psym->sym != lib_) {
	    if (str)
		free(str);
	    return value;
	}
    }

/*
    Search the local symbol table from the rear end to the front. This method
    is comparable with search_line, except that now the search is linear.
*/
    for (l_idx = last_index(&locals); l_idx >= 0; l_idx--) {
	psch = index_line(&locals, l_idx);
	psym = sym_getsym(psch->value);
	if (!strcmp(module ? str : name, psym->name)) {
	    if (str)
		free(str);
	    return psch->value;
	}
    }

/*
    If the section is PRIVATE, the symbol is added to the local table.
*/
    if (section == def_private) {
	if (value)
	    return value;
	sch.name = strdup(module ? str : name);
	sch.value = sym_addsym(sch.name, level);
	add_line(&locals, -1, &sch);
	if (str)
	    free(str);
/*
    It appears to be necessary to add local symbols to the search table;
    this means that they are visible to the global table.
*/
	goto einde;
    }

/*
    If a module is activem the name is added to the module name and the search
    is restarted. A new search is not executed in case the name was already
    found.
*/
    if (section == def_equal && module && g_idx > 0) {
	if (str)
	    free(str);
	return value;
    }

/*
    In section MODULE a new module name is created.
*/
    if (section == def_module) {
	if (module)
	    free(module);
	module = strdup(module ? str : name);
	if (str)
	    free(str);
	str = module;
    } else if (module && (g_idx = search_line(&search, str)) > 0) {
/*
    Search again the global symbol table in case str is filled thanks to
    module.
*/
	psch = index_line(&search, g_idx);
	if (str)
	    free(str);
	return psch->value;
    }

/*
    A symbol is recognized by name only. Redefinition is always possible.
    In that case it is not necessary to make a new entry in the table.
*/
    if (g_idx > 0) {
/*
    Correction in case a local symbol has been found.
*/
	psym = sym_getsym(value);
	if (psym->level)
	    value = 0;
	if (str)
	    free(str);
	return value;
    }

/*
    Module members are never added as a global symbol.
*/
    if (strchr(name + 1, '.') && !module && !value)
	return 0;

/*
    If the name was not found, a new symbol table entry is added.
*/
store:
    sch.name = strdup(module ? str : name);
    sch.value = sym_addsym(sch.name, 0);
    if (str && str != module)
	free(str);

einde:
    if (module)
	g_idx = search_line(&search, sch.name);
    if (g_idx <= 0)
	add_line(&search, -g_idx, &sch);
    return sch.value;
}

/*
    sym_getsym - given an index in the symbol table, return a pointer; that
		 pointer must be used before a new symbol is added.
*/
symbol_t *sym_getsym(int idx)
{
    return index_line(&global, idx);
}

/*
    sym_loop - given an index in the symbol table, return a pointer.
	       At this stage of the program, no new symbols are added.
*/
symbol_t *sym_loop(int idx, long *rv)
{
    search_t *sch;

    if ((sch = index_line(&search, idx)) == 0)
	return 0;
    return index_line(&global, *rv = sch->value);
}

static void endlevel()
{
    int idx;
    search_t *psch;
    symbol_t *psym;

    for (idx = last_index(&locals); idx >= 0; idx--) {
	psch = index_line(&locals, idx);
	psym = sym_getsym(psch->value);
	if (level == psym->level)
	    remove_line(&locals, idx);
	else
	    break;
    }
    if (--level < 0)
	level = 0;
}

static void endmodule()
{
    char *str;

    if ((str = strrchr(module, '.')) != 0)
	*str = 0;
    else if (module) {
	free(module);
	module = 0;
    }
}

/*
    module, private, public, equal, end and ;
*/
void sym_section(int mode)
{
    switch (mode) {
    case def_private :
	section = mode;
	level++;
	break;

    case def_end :
	endlevel();
	if (!level && module)
	    endmodule();
	/* continue */
	section = 0;
	break;

    case ';' :
	section = prev_section;
	break;

    case def_equal :
	prev_section = section;
	/* continue */

    default :
	section = mode;
	break;
    }
}

int sym_default()
{
    return !section;
}
