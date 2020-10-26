/*
    module  : strings.h
    version : 1.2
    date    : 10/26/20
*/
typedef struct string_t {
    char *str;
} string_t;

void str_init(void);
void str_exit(void);
char *str_get(int idx);
int str_add(char *str);
