/*
    module  : task.c
    version : 1.3
    date    : 09/15/23
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
    lst_init(ptr->stck);		/* start with an empty stack */
    lst_init(ptr->prog);		/* start with empty code */
    node = lst_pop(env->stck);		/* read the code from the stack */
    lst_copy(ptr->prog, node.u.lis);	/* copy the code to be executed */
    renew_thread(env);			/* switch to the new thread */
#endif
}
#endif
