/*
 *  module  : exeterm.c
 *  version : 1.10
 *  date    : 09/19/24
 */
#include "globals.h"

#ifdef TRACING
static void my_trace(pEnv env, Node node, FILE *fp)
{
    if (!env->debugging)
	return;
    writestack(env, env->stck, fp);
    fprintf(fp, " : ");
    writefactor(env, node, fp);
    fputc('\n', fp);
    fflush(fp);
}
#endif

/*
 * Execute program, as long as it is not empty.
 */
void exeterm(pEnv env, NodeList list)
{
    Node node;

    prog(env, list);
    while (vec_size(env->prog)) {
	node = vec_pop(env->prog);
#ifdef TRACING
	my_trace(env, node, stdout);
#endif
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
	vec_push(env->stck, node);
    }
}
