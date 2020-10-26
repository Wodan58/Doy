/*
    module  : set32.h
    version : 1.2
    date    : 10/26/20
*/
#define SETSIZE		  32
#define MAXINT	  2147483647

int set_bit(unsigned set, int bit);
int tst_bit(unsigned set, int bit);
int del_bit(unsigned set, int bit);
int set_drop(unsigned set, int bit);
int set_take(unsigned set, int bit);
