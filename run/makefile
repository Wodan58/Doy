#
#   module  : makefile
#   version : 1.3
#   date    : 11/23/20
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
CC = gcc -o$@
CFLAGS = -DNDEBUG -I.. -Os -Wall -Wextra

ARFLAGS = rv -U

DO = librun.a

RUNLIB : $(DO)(array.o) $(DO)(code.o) $(DO)(compile.o) $(DO)(convert2.o) \
	 $(DO)(convert.o) $(DO)(cycle.o) $(DO)(debug.o) $(DO)(dump.o) \
	 $(DO)(error.o) $(DO)(flex.o) $(DO)(initsym.o) $(DO)(input.o) \
	 $(DO)(interp.o) $(DO)(kons.o) $(DO)(listing.o) $(DO)(local.o) \
	 $(DO)(memory.o) $(DO)(nodes.o) $(DO)(print.o) $(DO)(readlib.o) \
	 $(DO)(set32.o) $(DO)(stack.o) $(DO)(stats.o) $(DO)(strings.o) \
	 $(DO)(token.o) $(DO)(value.o) $(DO)(writestr.o) $(DO)(ftoa.o)

clean:
	rm -f *.a
