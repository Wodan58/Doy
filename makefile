#
#   module  : makefile
#   version : 1.3
#   date    : 09/20/23
#
.POSIX:
.SUFFIXES:
.SUFFIXES: .c .o .joy

PROG   = fib
CC     = gcc
CFLAGS = -O3 -Wall -Wextra -Werror -Wno-unused-parameter
HDRS   = globals.h
OBJS   = $(PROG).o exeterm.o ersatz.o main.o exec.o writ.o prog.o save.o undo.o

$(PROG):	prep $(OBJS)
	$(CC) -o$@ $(OBJS) -lm -lgc

$(OBJS): $(HDRS)

prep:
	sh defs.sh .
	sh deps.sh .
	sh prim.sh .

.c.o:
	$(CC) -o$@ $(CFLAGS) -c $<

.joy.c:
	./joy -c $<

clean:
	rm -f *.o defs.h deps.h prim.c prim.h
