#
#   module  : makefile
#   version : 1.4
#   date    : 12/14/20
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
.PRECIOUS:
.SUFFIXES: .joy

ASM = nasm
AFLAGS = -o$@ -felf64 -l$*.lst

CC = gcc -o$@
CFLAGS = -DNDEBUG -Os -Wall -Wextra -Werror

LD = gcc -o$@
LFLAGS = -Lrun -lrun -Lsrc -ldo

OBJECT  = joy0.o lookup1.o symbol.o factor.o data2.o 
RUNTIME = main.o tutorial.o lookup.o symbol.o factor.o data.o
TOKENS  = token2.o lookup1.o symbol.o factor.o data2.o
COMPILE = spasm.o lookup2.o symbol2.o factor2.o data2.o
DUPLO	= duplo.o fib.o lookup.o factor.o data.o

dummy : RUNLIB DOLIB joy0 joy1 JOYLIB JOYTEST

DOLIB :
	$(MAKE) -C src

RUNLIB :
	$(MAKE) -C run

JOYLIB :
	$(MAKE) -C lib

JOYTEST:
	$(MAKE) -C test

joy0: tutorial
	./tutorial <input.txt

tutorial: joy tutorial.s $(RUNTIME)
	$(LD) $(RUNTIME) $(LFLAGS)

joy: $(OBJECT)
	$(LD) $(OBJECT) $(LFLAGS)

tutorial.s: tutorial.joy
	./joy -c <$< >$@

token: $(TOKENS)
	$(LD) $(TOKENS) $(LFLAGS)

spasm: $(COMPILE)
	$(LD) $(COMPILE) $(LFLAGS)

duplo: spasm $(DUPLO)
	$(LD) $(DUPLO) $(LFLAGS)

joy1: duplo
	./duplo

.s.o:
	$(ASM) $(AFLAGS) $<

.joy.s:
	./spasm $< >$@

clean:
	rm -f *.o *.s *.lst *.out tutorial joy token spasm duplo
	$(MAKE) -C src clean
	$(MAKE) -C run clean
	$(MAKE) -C lib clean
