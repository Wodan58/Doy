/*
    module  : code.h
    version : 1.2
    date    : 10/26/20
*/
typedef void (*proc_t)(void);

void put(long num);
void rev(int start, int einde);
void proc(data_t *cur);
long pop(void);
void loop(void);
int user(long num);
void exeterm(data_t *cur);
int used(void);
long peek(int i);
void poke(int i, long num);
void empty(void);
