/*
    module  : recv.c
    version : 1.3
    date    : 09/15/23
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
    temp = lst_back(env->stck);		/* receive a node from the channel, */ 
    if (receive(env, temp.u.num, &node))
	lst_push(env->stck, node);	/* push it on the stack and continue */
    else {
	node.u.proc = recv_;		/* reschedule this instruction */
	node.op = ANON_FUNCT_;
	lst_push(env->prog, node);
	release(env);			/* switch to another task */
    }
#endif
}
#endif
