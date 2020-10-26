/*
    module  : array.h
    version : 1.2
    date    : 10/26/20
*/
typedef struct array_t {
     int count,    /* number of lines that are present */
	 current,  /* current capacity of lines        */
	 previous, /* previous capacity of lines       */
	 width,    /* width of a line in bytes         */
	 size;     /* total number of bytes            */
    char *table;   /* table with data                  */
} array_t;

void init_array(array_t *arr, int width);
int last_index(array_t *arr);
void *index_line(array_t *arr, int lineno);
int remove_line(array_t *arr, int lineno);
int add_line(array_t *arr, int lineno, void *line);
int search_line(array_t *arr, void *key);
