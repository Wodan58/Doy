/*
    module  : data.h
    version : 1.2
    date    : 10/26/20
*/

/*
    data_t is used to store data on the stack.
    because of alignment it is better to have the value field last.
*/
typedef struct data_t {
    int op;
    struct data_t *next;
    union {
	long num;		/* SYMBOL, LOGICAL, CHAR, INTEGER, SET */
	char *str;		/* STRING */
	struct data_t *list;	/* LIST */
	double dbl;		/* FLOAT */
	FILE *fp;		/* FILE */
	long val;
    };
} data_t;

extern data_t *stack, *dump, *dump1, *dump2, *dump3, *dump4, *dump5;

/*
    Get is used to ask for a number of nodes at one go;
    the nodes are stored at consecutive addresses.
*/
void gc(void);
void reg(data_t **list);
data_t *get(int num);
void mrep(long *size, long *prev, long *used);

void debug(const char *name);
extern double stat_ops;

#define DEBUG(x)	stat_ops++
