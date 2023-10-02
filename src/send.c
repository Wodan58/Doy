/*
    module  : send.c
    version : 1.4
    date    : 10/02/23
*/
#ifndef SEND_C
#define SEND_C

/**
OK 3290  send  :  DDA	C  N  ->  C
[MT] Send a node through a channel and switch to the next task.
*/
void send_(pEnv env)
{
#ifdef MULTI_TASK_THREAD_JOY
    Node node, temp;

    PARM(2, SEND);
    env->stck = pvec_pop(env->stck, &node); /* read the node from the stack */
    temp = pvec_lst(env->stck);		/* send the node through the channel */
    send(env, temp.u.num, node);	/* use channel number */
#endif
}
#endif
