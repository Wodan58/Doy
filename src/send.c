/*
    module  : send.c
    version : 1.3
    date    : 09/15/23
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
    node = lst_pop(env->stck);		/* read the node from the stack */
    temp = lst_back(env->stck);		/* send the node through the channel */
    send(env, temp.u.num, node);	/* use channel number */
#endif
}
#endif
