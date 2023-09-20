/*
 *  module  : exeterm.c
 *  version : 1.3
 *  date    : 09/20/23
 */
#include "globals.h"

/*
    Execute program, as long as it is not empty.
*/
PUBLIC void exeterm(pEnv env, NodeList *list)
{
    Node node;

    lst_copy(env->prog, list);
    while (lst_size(env->prog)) {
	node = lst_pop(env->prog);
	switch (node.op) {
	case USR_LIST_:
	    prog(env, node.u.lis);
	    break;
	case ANON_FUNCT_:
	    (*node.u.proc)(env);
	    break;
	case USR_PRIME_:
	    node.op = USR_;
	    goto next;
	case ANON_PRIME_:
	    node.op = ANON_FUNCT_;
	    goto next;
next:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	case BIGNUM_:
	case USR_STRING_:
	    lst_push(env->stck, node);
	    break;
	}
    }
}
