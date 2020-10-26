/*
    module  : token2.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <ctype.h>
#include "ident.h"
#include "symbol.h"
#include "token.h"
#include "set32.h"
#include "initsym.h"
#include "input.h"
#include "local.h"
#include "lookup.h"
#include "listing.h"

/*
    val -> num, str, dbl
*/
static void writetoken()
{
    int i;
    symbol_t *psym;

    switch (sym) {
    case typ_logical :
        psym = sym_getsym(val.num ? sym_true : sym_false);
        printf("%s (%ld)", psym->name, val.num);
	break;

    case typ_char    :
	if (isprint(val.num))
	    printf("'%c", (int)val.num);
	else
	    printf("'\\%03d", (int)val.num);
	break;

    case typ_integer :
	printf("%ld", val.num);
	break;

    case typ_set     :
	printf("{ ");
	for (i = 0; i < SETSIZE; i++)
	    if (tst_bit(val.num, i))
		printf("%d ", i);
	printf("}");
	break;

    case typ_string  :
	putchar('"');
	for (i = 0; val.str[i]; i++)
	    if (val.str[i] == '\n')
		printf("\\n");
	    else
		putchar(val.str[i]);
	putchar('"');
	break;

    case typ_float   :
	printf("%g", val.dbl);
	break;

    case typ_file    :
	printf("%08lX", val.num);
	break;

    case typ_symbol  :
        psym = sym_getsym(val.num);
        printf("%s (%ld)", psym->name, val.num);
	break;

    default :
	printf("%c", sym);
	break;
    }
    putchar('\n');
}

int main(int argc, char *argv[])
{
    initlisting("token.lst");
    initialise();
    lookup0();
    inp_init();
    if (argc > 1)
	firstfile(argv[1]);
    while (sym != EOF) {
	getsym();
	switch (sym) {
	case def_module :
	    printf("MODULE\n");
	    break;

	case def_private :
	    printf("PRIVATE\n");
	    break;

	case def_public :
	    printf("PUBLIC\n");
	    break;

	case def_equal :
	    printf("==\n");
	    break;

	case def_end :
	    printf("END\n");
	    break;

	case EOF :
	    printf("EOF\n");
	    break;

	default :
	    writetoken();
	    break;
	}
    }
    return 0;
}
