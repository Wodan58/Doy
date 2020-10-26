/*
    module  : compile.c
    version : 1.2
    date    : 10/26/20

	void compileterm(int n)
	void initcompile(void)
	void compilelib(void)
	void compilestop(void)
*/
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "ident.h"
#include "memory.h"
#include "symbol.h"
#include "boole.h"
#include "strings.h"
#include "writestr.h"
#include "compile.h"

/*
mul	*
add	+
sub	-
divide  /

rem
mod
neg	not for unsigned
abs		,,
sign		,,

eql	=
neq	!=
neq     <>
lss	<
leq	<=
gtr	>
geq	>=
*/
static struct typname {
    unsigned char print;
    char *name, *altname;
} typname[9];

static struct typname *get_typname(int typ)
{
    if (!typname[0].name) {
	typname[0].name = "user";
	typname[0].altname = "user";
	typname[1].name = "logical";
	typname[1].altname = "logical";
	typname[2].name = "char";
	typname[2].altname = "char";
	typname[3].name = "integer";
	typname[3].altname = "integer";
	typname[4].name = "set";
	typname[4].altname = "set";
	typname[5].name = "string";
	typname[5].altname = "string";
	typname[6].name = "list";
	typname[6].altname = "list";
	typname[7].name = "float";
	typname[7].altname = "float";
	typname[8].name = "file";
	typname[8].altname = "file";
    }
    if ((typ -= typ_symbol) < 1 || typ > 8)
	return 0;
    return typname + typ;
}

static char *get_altname(char *str)
{
    int i;

    switch (*str) {
    case '*' :
	if (!str[1])
	    return "mul";
	break;

    case '+' :
	if (!str[1])
	    return "add";
	break;

    case '-' :
	if (!str[1])
	    return "sub";
	break;

    case '/' :
	if (!str[1])
	    return "divide";
	break;

    case '<' :
	if (!str[1])
	    return "lss";
	if (str[1] == '=' && !str[2])
	    return "leq";
	if (str[1] == '>' && !str[2])
	    return "neq";
	break;

    case '=' :
	if (!str[1])
	    return "eql";
	break;

    case '!' :
	if (str[1] == '=' && !str[2])
	    return "neq";
	break;

    case '>' :
	if (!str[1])
	    return "gtr";
	if (str[1] == '=' && !str[2])
	    return "geq";
	break;

    case '.' :
	if (!str[1])
	    return "stop";
	break;

    case '_' :
	if (!strcmp(str, "_help"))
	    return "help1";
	if (!strcmp(str, "_genrec"))
	    return "aux_genrec";
	if (!strcmp(str, "_treerec"))
	    return "aux_treerec";
	if (!strcmp(str, "_treegenrec"))
	    return "aux_treegenrec";
	while (*++str == '_')
	    ;
	break;
    }
    for (i = 0; i < 8; i++)
	if (!strcmp(str, typname[i].name))
	    return typname[i].altname;
    return str;
}

static void initdata()
{
    int idx;
    symbol_t *psym;

    idx = sym_lookup("nothing");
    psym = sym_getsym(idx);
    psym->used = 1;
    idx = sym_lookup("false");
    psym = sym_getsym(idx);
    psym->used = 1;
    idx = sym_lookup("true");
    psym = sym_getsym(idx);
    psym->used = 1;
}

static void check_special(int id)
{
    int idx;
    symbol_t *psym;

    if (id == genrec_) {
	idx = sym_lookup("_genrec");
	psym = sym_getsym(idx);
	psym->used = 1;
    }
    if (id == treerec_) {
	idx = sym_lookup("_treerec");
	psym = sym_getsym(idx);
	psym->used = 1;
    }
    if (id == treegenrec_) {
	idx = sym_lookup("_treegenrec");
	psym = sym_getsym(idx);
	psym->used = 1;
    }
}

static void compilefactor(int n, int p);
static void compilefactorlevel(int n);

void compileterm(int n, int p)
{
    memory_t *pmem;

    while (n > 0) {
	pmem = mem_get(n);
	compilefactor(n, p);
	n = pmem->nxt;
    }
}  /* compileterm */

static void compiletermlevel(int n)
{
    memory_t *pmem;

    while (n > 0) {
	pmem = mem_get(n);
	compilefactorlevel(n);
	n = pmem->nxt;
    }
}  /* compiletermlevel */

static void compilefactor(int n, int p)
{
    int next;
    char *name;
    memory_t *pmem;
    symbol_t *psym;
    struct typname *ptyp;

    if (n > 0) {
	pmem = mem_get(n);
	next = pmem->nxt;
	printf("L%d", n);
	next = p || next;
	switch (pmem->op) {
	case typ_list     :
	    if (pmem->val)
		printf("\tmov\trdi,L%ld\n", pmem->val);
	    else
		printf("\tmov\trdi,0\n");
	    break;

	case typ_string   :
	    printf("\tmov\trdi,T%d\n", str_add((char *)pmem->val));
	    break;

	case typ_logical  :
	case typ_set      :
	case typ_char     :
	case typ_integer  :
	case typ_float    :
	case typ_file     :
	    printf("\tmov\trdi,%ld\n", pmem->val);
	    break;
	default :
	    break;
	}
	if ((ptyp = get_typname(pmem->op)) != 0)
	    if (!ptyp->print) {
		ptyp->print = 1;
		printf("\textern\tis_%s\n", ptyp->name);
	    }
	switch (pmem->op) {
	case typ_list    :
	    printf("\t%s\tis_%s\n", next ? "call" : "jmp", ptyp->name);
	    printf("\tsection .data\n");
	    compiletermlevel(pmem->val);
	    printf("\tsection .text\n");
	    break;

	case typ_string  :
	    printf("\t%s\tis_%s\n", next ? "call" : "jmp", ptyp->name);
	    break;

	case typ_logical :
	case typ_set     :
	case typ_char    :
	case typ_integer :
	case typ_float   :
	case typ_file    :
	    printf("\t%s\tis_%s\n", next ? "call" : "jmp", ptyp->name);
	    break;

	default :
	    psym = sym_getsym(pmem->val);
	    if (!psym->used)
		psym->used = 1;
	    if (!psym->id) {
		printf("\tmov\trdi,U%ld\n", pmem->val);
		if ((ptyp = get_typname(typ_symbol)) == 0)
		    ptyp = typname;
		if (!ptyp->print) {
		    ptyp->print = 1;
		    printf("\textern\tis_user\n");
		}
		printf("\t%s\tis_user\n", next ? "call" : "jmp");
	    } else {
		name = get_altname(psym->name);
		if (!psym->print) {
		    psym->print = 1;
		    printf("\textern\tdo_%s\n", name);
		}
		printf("\t%s\tdo_%s\n", next ? "call" : "jmp", name);
		check_special(psym->id);
	    }
	    break;
	}  /* CASE */
    }
}  /* compilefactor */

static void compilefactorlevel(int n)
{
    memory_t *pmem;
    symbol_t *psym;

    if (n > 0) {
	printf("L%d", n);
	pmem = mem_get(n);
	if (pmem->op >= typ_symbol && pmem->op <= typ_function)
	    printf("\tdq\t%d\n", pmem->op);
	else
	    printf("\tdq\t%d\n", typ_symbol);
	if (pmem->nxt)
	    printf("\tdq\tL%d\n", pmem->nxt);
	else
	    printf("\tdq\t0\n");
	switch (pmem->op) {
	case typ_list    :
	    if (pmem->val)
		printf("\tdq\tL%ld\n", pmem->val);
	    else
		printf("\tdq\t0\n");
	    compiletermlevel(pmem->val);
	    break;

	case typ_string  :
	    printf("\tdq\tT%d\n", str_add((char *)pmem->val));
	    break;

	case typ_logical :
	case typ_set     :
	case typ_char    :
	case typ_integer :
	case typ_float   :
	case typ_file    :
	    printf("\tdq\t%ld\n", pmem->val);
	    break;

	default :
	    printf("\tdq\tU%ld\n", pmem->val);
	    psym = sym_getsym(pmem->val);
	    if (!psym->used)
		psym->used = 1;
	    check_special(psym->id);
	    break;
	}  /* CASE */
    }
}  /* compilefactorlevel */

void initcompile()
{
    printf("\tbits\t64\n");
    printf("\tdefault\trel\n");
    printf("\tsection .data\n");
    printf("\tglobal\tjoy_data\njoy_data:\n");
    printf("\tsection .text\n");
    printf("\textern\tnl\n");
    printf("\tglobal\tjoy_text\njoy_text:\n");
    initdata();
}

void compilestop()
{
    int idx;
    symbol_t *psym;

    idx = sym_lookup(".");
    psym = sym_getsym(idx);
    if (!psym->used)
	psym->used = 1;
    printf("\textern\tdo_stop\n");
    printf("\tcall\tdo_stop\n");
}

void compilelib()
{
    long j;
    char *name;
    symbol_t *psym;
    int i, k, found;

    printf("L0\tret\n");
    printf("\tglobal\tend_text\nend_text:\n");
    printf("\tsection .data\n");
    do
	for (found = FALSE, i = 1; (psym = sym_getsym(i)) != 0; i++)
	    if (psym->used == 1 && psym->value) {
		psym->used = 2;
		compiletermlevel(psym->value);
		found = TRUE;
	    }
    while (found);
    printf("\tglobal\tjoy_table\njoy_table:\n");
    for (i = 0; (psym = sym_loop(i, &j)) != 0; i++) {
	if (psym->name[0] == '.' && psym->name[1])
	    continue;
	if (psym->used) {
	    printf("\tdq\tS%ld\n", j);
	    if (psym->id) {
		name = get_altname(psym->name);
		if (!psym->print) {
		    printf("\textern\tdo_%s\n", name);
		}
		printf("\tdq\tdo_%s\n", name);
	    } else if (psym->value)
		printf("\tdq\tL%ld\n", psym->value);
	    else
		printf("\tdq\t0\n");
	}
    }
    printf("\tglobal\tend_table\nend_table:\n");
    for (i = 0; (psym = sym_getsym(i)) != 0; i++) {
	if (psym->name[0] == '.' && psym->name[1])
	    continue;
	if (psym->used && psym->name) {
	    printf("S%d\tdb\t", i);
	    writestr(psym->name);
	}
    }
    for (i = 1; (name = str_get(i)) != 0; i++) {
	printf("T%d\tdb\t", i);
	writestr(name);
    }
    for (i = k = 0; (psym = sym_loop(i, &j)) != 0; i++) {
	if (psym->name[0] == '.' && psym->name[1])
	    continue;
	if (psym->used)
	    printf("U%ld\tequ\t%d\n", j, k++);
    }
    printf("\tglobal\tend_data\nend_data:\n");
}  /* compilelib */
