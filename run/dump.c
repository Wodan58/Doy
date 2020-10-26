/*
    module  : dump.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "memory.h"
#include "symbol.h"
#include "ident.h"
#include "convert.h"

char *standardident_NAMES[] = {
    "LIB", "SYMBOL", "BOOLEAN", "CHAR", "INTEGER", "SET", "STRING", "LIST",
    "FLOAT", "FILE", "FUNCTION",
    "MODULE", "PRIVATE", "PUBLIC", "==", "END",
    "%IF", "%INCLUDE", "%LISTING", "%PUT", "%RADIX", "%SET", "%STATISTICS",
    "%TRACE",
    "*", "+", "-", "/", "<", "=", "and", "body", "cons", "dip", "dup", "false",
    "get", "getch", "i", "index", "not", "nothing", "or", "pop", "put",
    "putch", "sametype", "select", "stack", "step", "swap", "true", "uncons",
    "unstack", "maxint",
    "_genrec", "_treerec", "_treegenrec", "setsize", "__symtabmax",
    "__symtabindex", "__dump", "conts", "autoput", "undeferror", "undefs",
    "echo", "clock", "time", "rand", "__memorymax", "stdin", "stdout",
    "stderr", "id", "rollup", "rolldown", "rotate", "popd", "dupd", "swapd",
    "rollupd", "rolldownd", "rotated", "choice", "xor", "rem", "div", "sign",
    "neg", "ord", "chr", "abs", "acos", "asin", "atan", "atan2", "ceil", "cos",
    "cosh", "exp", "floor", "frexp", "ldexp", "log", "log10", "modf", "pow",
    "sin", "sinh", "sqrt", "tan", "tanh", "trunc", "localtime", "gmtime",
    "mktime", "strfime", "strtol", "strtod", "format", "formatf", "srand",
    "pred", "succ", "max", "min", "fclose", "feof", "ferror", "fflush",
    "fgetch", "fgets", "fopen", "fread", "fwrite", "fremove", "frename",
    "fput", "fputch", "fputchars", "fputstring", "fseek", "ftell", "swons",
    "first", "rest", "compare", "at", "of", "size", "opcase", "case",
    "unswons", "drop", "take", "concat", "enconcat", "name", "intern", "null",
    "small", ">=", ">", "<=", "!=", "equal", "has", "in", "integer", "char",
    "logical", "set", "string", "list", "leaf", "user", "float", "file", "x",
    "app1", "app11", "app12", "construct", "nullary", "unary", "unary2",
    "unary3", "unary4", "app2", "app3", "app4", "binary", "ternary", "cleave",
    "branch", "ifte", "ifinteger", "ifchar", "iflogical", "ifset", "ifstring",
    "iflist", "iffloat", "iffile", "cond", "while", "linrec", "tailrec",
    "binrec", "genrec", "condnestrec", "condlinrec", "fold", "map", "times",
    "infra", "primrec", "filter", "split", "some", "all", "treestep",
    "treerec", "treegenrec", "help", "_help", "helpdetail", "manual",
    "__html_manual", "__latex_manual", "__manual_list", "__settracegc",
    "setautoput", "setundeferror", "setecho", "gc", "system", "getenv", "argv",
    "argc", "__memoryindex", "putchars", "include", "abort", "quit",
    "__setlisting", "__setstats", "__settrace", "builtin", "fget", "mod",
    ".", "UNKNOWN"
};

void DumpM(int num)
{
    long i;
    FILE *fp;
    symbol_t *psym;
    memory_t *node;
    char str[20], *name;

    sprintf(str, "joy%d.dmp", num);
    if ((fp = fopen(str, "w")) == 0)
	return;
    fprintf(fp, "Table\n");
    fprintf(fp, "  nr %-*.*s  adr sym  id\n", identlength, identlength, "name");
    for (i = 1; (psym = sym_getsym(i)) != 0; i++)
	fprintf(fp, "%4ld %-*.*s %4ld %3ld %3ld\n", i, identlength, identlength,
		psym->name, psym->value, (long)psym->sym, (long)psym->id);
    fprintf(fp, "\nMemory\n");
    fprintf(fp, "  nr %-*.*s      value next  alt M\n", identlength,
	    identlength, "name");
    for (i = 1; (node = mem_get(i)) != 0; i++) {
	if (node->op == typ_symbol || node->op == typ_function)
	    name = sym_getsym(node->val)->name;
	else
	    name = standardident_NAMES[node->op];
	fprintf(fp, "%4ld %-*.*s %10ld %4ld %4ld %c\n", i, identlength,
		identlength, name, node->val, (long)node->nxt,
		0L,
		node->marked ? 'T' : 'F');
    }
    fclose(fp);
}
