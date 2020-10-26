/*
    module  : convert.h
    version : 1.2
    date    : 10/26/20
*/
#define identlength	16	/* maximum length of an identifier */

memrange ReadTerm(void);
memrange ReadFactor(void);

void WriteTerm(memrange n);
void WriteFactor(memrange n);
void WriteLine(void);
void WriteString(char *str);
void WriteChar(int ch);
