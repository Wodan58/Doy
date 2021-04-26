/*
    module  : strings.h
    version : 1.3
    date    : 04/24/21
*/
typedef struct my_string_t {
    char *str;
} my_string_t;

void str_init(void);
void str_exit(void);
char *str_get(int idx);
int str_add(char *str);
