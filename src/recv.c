/*
    module  : recv.c
    version : 1.4
    date    : 10/02/23
*/
#ifndef RECV_C
#define RECV_C

/**
OK 3280  recv  :  DAA	P  ->  P  N
[MT] Receive a node from a channel and push it on the stack.
*/
void recv_(pEnv env)
{
#ifdef MULTI_TASK_THREAD_JOY
    Node temp, node;

    PARM(1, RECEIVE);
    temp = pvec_lst(env->stck);		/* receive a node from the channel, */ 
    if (receive(env, temp.u.num, &node))
	env->stck = pvec_add(env->stck, node);	/* push it on the stack */
    else {
	code(env, recv_);		/* reschedule this instruction */
	release(env);			/* switch to another task */
    }
#endif
}
#endif
