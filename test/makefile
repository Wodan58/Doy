#
#   module  : makefile
#   version : 1.1
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
.SUFFIXES: .joy .s .o

ASM = nasm
AFLAGS = -o$@ -felf64 -l$*.lst

CC = gcc -o$@
CFLAGS = -DNDEBUG -Os -Wall -Wextra -Werror

LD = gcc -o$@
LFLAGS = -L../run -lrun -L../src -ldo -lm

DUPLO = ../duplo.o ../lookup.o ../factor.o ../data.o

dummy: test02 test03 test04 test05 test06 test07 test09 test11 test12 test13 test14

test01: test01.o $(DUPLO)
	-$(LD) test01.o $(DUPLO) $(LFLAGS)
	-./test01

test02: test02.o $(DUPLO)
	-$(LD) test02.o $(DUPLO) $(LFLAGS)
	-./test02

test03: test03.o $(DUPLO)
	-$(LD) test03.o $(DUPLO) $(LFLAGS)
	-./test03

test04: test04.o $(DUPLO)
	-$(LD) test04.o $(DUPLO) $(LFLAGS)
	-./test04

test05: test05.o $(DUPLO)
	-$(LD) test05.o $(DUPLO) $(LFLAGS)
	-./test05 test05.joy

test06: test06.o $(DUPLO)
	-$(LD) test06.o $(DUPLO) $(LFLAGS)
	-./test06 <text

test07: test07.o $(DUPLO)
	-$(LD) test07.o $(DUPLO) $(LFLAGS)
	-./test07

#test08: test08.o $(DUPLO)
#	-$(LD) test08.o $(DUPLO) $(LFLAGS)
#	-./test08

test09: test09.o $(DUPLO)
	-$(LD) test09.o $(DUPLO) $(LFLAGS)
	-./test09

test10: test10.o $(DUPLO)
	-$(LD) test10.o $(DUPLO) $(LFLAGS)
	-./test10

test11: test11.o $(DUPLO)
	-$(LD) test11.o $(DUPLO) $(LFLAGS)
	-./test11

test12: test12.o $(DUPLO)
	-$(LD) test12.o $(DUPLO) $(LFLAGS)
	-./test12

test13: test13.o $(DUPLO)
	-$(LD) test13.o $(DUPLO) $(LFLAGS)
	-./test13

test14: test14.o $(DUPLO)
	-$(LD) test14.o $(DUPLO) $(LFLAGS)
	-./test14

.s.o:
	-$(ASM) $(AFLAGS) $<

.joy.s:
	-../spasm $< >$@

clean:
	rm -f *.o *.s *.lst *.out test01 test02 test03 test04 test05 test06 test07 test08 test09 test10 test11 test12 test13 test14 tekst test1
