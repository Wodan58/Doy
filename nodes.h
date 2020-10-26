/*
    module  : nodes.h
    version : 1.2
    date    : 10/26/20
*/
#pragma pack(1)
typedef struct node_t {
    unsigned char op;	// 0xB9
    long val;		// value to be moved
    unsigned char call;	// 0xE8
    long adr;		// address to be called
} node_t;
#pragma pack()

int readcode(node_t *cur, data_t *node);
void printprogram(unsigned char *prog, FILE *fp);
