/*
 *  module  : exeterm.c
 *  version : 1.8
 *  date    : 04/13/24
 */
#include "globals.h"

/*
 * Execute program, as long as it is not empty.
 */
void exeterm(pEnv env, NodeList *list)
{
    Node node;

    prog(env, list);
    while (pvec_cnt(env->prog)) {
	env->prog = pvec_pop(env->prog, &node);
	switch (node.op) {
	case USR_LIST_:
	    prog(env, node.u.lis);
	    continue;
	case ANON_FUNCT_:
	    (*node.u.proc)(env);
	    continue;
	case USR_PRIME_:
	    node.op = USR_;
	    break;
	case ANON_PRIME_:
	    node.op = ANON_FUNCT_;
	    break;
	}
	env->stck = pvec_add(env->stck, node);
    }
}
