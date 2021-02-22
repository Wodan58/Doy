#
#   module  : makefile
#   version : 1.3
#   date    : 02/22/21
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
MYLIB = ../rand.o ../srand.o

dummy: gcd1 modtst1 test1 tutinp1 alljoy1 jp-reprodtst1 mtrtst1 jp-church1 flatjoy1 reptst1 symtst1 jp-joytst1 plgtst1 laztst1 jp-nestrec1 grmtst1 lsptst1 # mandel1

gcd: gcd.o $(DUPLO)
	-$(LD) gcd.o $(DUPLO) $(LFLAGS)

gcd1: gcd
	-./gcd 24 54 | diff -w - OUT/gcd.out

modtst: modtst.o $(DUPLO)
	-$(LD) modtst.o $(DUPLO) $(LFLAGS)

modtst1: modtst
	-./modtst 2>/dev/null | diff -w - OUT/modtst.out

test: test.o $(DUPLO)
	-$(LD) test.o $(DUPLO) $(LFLAGS)

test1: test
	-./test | diff -w - OUT/test.out

tutinp: tutinp.o $(DUPLO) $(MYLIB)
	-$(LD) tutinp.o $(DUPLO) $(MYLIB) $(LFLAGS)

tutinp1: tutinp
	-./tutinp tutinp.inp | diff -w - OUT/tutinp.out

alljoy: alljoy.o $(DUPLO)
	-$(LD) alljoy.o $(DUPLO) $(LFLAGS)

alljoy1: alljoy
	-./alljoy | diff -w - OUT/alljoy.out

jp-reprodtst: jp-reprodtst.o $(DUPLO)
	-$(LD) jp-reprodtst.o $(DUPLO) $(LFLAGS)

jp-reprodtst1: jp-reprodtst
	-./jp-reprodtst | diff -w - OUT/jp-reprodtst.out

mtrtst: mtrtst.o $(DUPLO)
	-$(LD) mtrtst.o $(DUPLO) $(LFLAGS)

mtrtst1: mtrtst
	-./mtrtst | diff -w - OUT/mtrtst.out

jp-church: jp-church.o $(DUPLO)
	-$(LD) jp-church.o $(DUPLO) $(LFLAGS)

jp-church1: jp-church
	-./jp-church | diff -w - OUT/jp-church.out

flatjoy: flatjoy.o $(DUPLO)
	-$(LD) flatjoy.o $(DUPLO) $(LFLAGS)

flatjoy1: flatjoy
	-./flatjoy | diff -w - OUT/flatjoy.out

reptst: reptst.o $(DUPLO)
	-$(LD) reptst.o $(DUPLO) $(LFLAGS)

reptst1: reptst
	-./reptst | diff -w - OUT/reptst.out

symtst: symtst.o $(DUPLO)
	-$(LD) symtst.o $(DUPLO) $(LFLAGS)

symtst1: symtst
	-./symtst | diff -w - OUT/symtst.out

jp-joytst: jp-joytst.o $(DUPLO)
	-$(LD) jp-joytst.o $(DUPLO) $(LFLAGS)

jp-joytst1: jp-joytst
	-./jp-joytst | diff -w - OUT/jp-joytst.out

plgtst: plgtst.o $(DUPLO)
	-$(LD) plgtst.o $(DUPLO) $(LFLAGS)

plgtst1: plgtst
	-./plgtst | diff -w - OUT/plgtst.out

lsptst: lsptst.o $(DUPLO)
	-$(LD) lsptst.o $(DUPLO) $(LFLAGS)

lsptst1: lsptst
	-./lsptst lsptst.inp | diff -w - OUT/lsptst.out

laztst: laztst.o $(DUPLO)
	-$(LD) laztst.o $(DUPLO) $(LFLAGS)

laztst1: laztst
	-./laztst | diff -w - OUT/laztst.out

jp-nestrec: jp-nestrec.o $(DUPLO)
	-$(LD) jp-nestrec.o $(DUPLO) $(LFLAGS)

jp-nestrec1: jp-nestrec
	-./jp-nestrec | diff -w - OUT/jp-nestrec.out

mandel: mandel.o $(DUPLO)
	-$(LD) mandel.o $(DUPLO) $(LFLAGS)

mandel1: mandel
	-./mandel | diff -w - OUT/mandel.out

grmtst: grmtst.o $(DUPLO)
	-$(LD) grmtst.o $(DUPLO) $(LFLAGS)

grmtst1: grmtst
	-./grmtst | diff -w - OUT/grmtst.out

.s.o:
	-$(ASM) $(AFLAGS) $<

.joy.s:
	-../spasm $< >$@

clean:
	rm -f *.o *.s *.lst *.out gcd modtst test tutinp alljoy jp-reprodtst mtrtst jp-church flatjoy reptst symtst jp-joytst plgtst lsptst laztst jp-nestrec mandel grmtst
