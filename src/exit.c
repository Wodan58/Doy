/*
    module  : exit.c
    version : 1.3
    date    : 09/15/23
*/
#ifndef EXIT_C
#define EXIT_C

/**
OK 3260  exit  :  N	->
[MT] Exit a thread.
*/
void exit_(pEnv env)
{
#ifdef MULTI_TASK_THREAD_JOY
    exit_thread(env);			/* exit a thread */
#endif
}
#endif
