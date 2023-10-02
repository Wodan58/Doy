/*
    module  : task.c
    version : 1.4
    date    : 10/02/23
*/
#ifndef TASK_C
#define TASK_C

/**
OK 3300  task  :  D	Q  ->
[MT] Execute quotation Q in a separate thread.
*/
void task_(pEnv env)
{
#ifdef MULTI_TASK_THREAD_JOY
    Node node;
    Context *ptr;

    PARM(1, DIP);
    ptr = new_thread(env);		/* create a new thread, no switch */
    ptr->stck = pvec_init();		/* start with an empty stack */
    ptr->prog = pvec_init();		/* start with empty code */
    env->stck = pvec_pop(env->stck, &node); /* read the code from the stack */
    pvec_copy(env->prog, node.u.lis);	/* copy the code to be executed */
    renew_thread(env);			/* switch to the new thread */
#endif
}
#endif
