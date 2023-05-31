#
#   module  : %M%
#   version : %I%
#   date    : %G%
#
#	Makefile voor various versions of Joy.
#
#	Joy is a translation of the Pascal sources, with a number of
#	corrections, extended with getch and putch and hyphen not as a
#	separate symbol.
#
#	Recipe for adding a new builtin:
#
#	1. Create a .c file with the code of the new builtin
#	2. Add the .c file to the makefile
#	3. Add the new builtin to standardindent in ident.h
#	4. Add the new builtin to initialise in initsym.c
#	5. Add the name of the builtin to standardident_NAMES in dump.c
#	6. Add a description of the builtin to prims.c
#
.SUFFIXES:
.SUFFIXES: .c .s .o

ASM = nasm
AFLAGS = -o$@ -felf64 -l$*.lst

CC = gcc -o$@
CFLAGS = -DNDEBUG -Os -Wall -Wextra

LD = gcc -o$@
LFLAGS = -Lrun -lrun

OBJECT = joy0.o lookup1.o symbol.o factor.o data2.o 

tut: joy
	./joy 42minjoy.lib tutorial.joy

joy: $(OBJECT) run/librun.a src/libdo.a
	$(LD) $(OBJECT) $(LFLAGS)

run/librun.a:
	$(MAKE) -C run

src/libdo.a:
	$(MAKE) -C src

.s.o:
	$(ASM) $(AFLAGS) $<

clean:
	rm -f *.o *.s *.lst *.out tutorial joy token spasm duplo
	$(MAKE) -C src clean
	$(MAKE) -C run clean
	$(MAKE) -C lib clean
	$(MAKE) -C test clean
