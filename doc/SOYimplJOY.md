 ![](Wynn.PNG)
==============

Introduction
============

Soy contains the runtime files for programs compiled by Moy. The files in de
src-directory are the same as in Moy.

Compiler
========

This document presents the advantages and disadvantages of compiling Moy
programs into Roy or Soy executables.

Advantages
----------

- There is no symbol table. There is no need for a symbol table, because
  symbols have already been translated to addresses.
- Libraries need not be read. Definitions in libraries are not needed in the
  compiled executable. Those definitions that were used in the program have
  already been incorporated in that executable.
- There is only one binary file instead of a number of source files. This makes
  maintenance and deployment easier.
- Execution is always a bit faster than in the interpreter, even when exactly
  the same code is executed because the source code need not be read and also
  because the compiled code is more compact and cache friendly.
- The source code is not visible. The user of the program only gets to see is
  the behaviour of the program and if that is satisfactory then there is no
  need to expose the source code.
- A programming language that comes with a compiler looks slightly more adult
  than a programming languages that only operates on source code.

Disadvantages
-------------

- A compiled program has limitied functionality compared with the interpreter.
  It can do only one thing.
- Binaries take up more hard disk space than the source files that the
  interpreter uses.
- An edit-compile-run sequence is longer and slower than an edit-run sequence.
  This makes program development slower.
- There are not as many debugging options when running a compiled program as
  there are when running the interpreter.
- The arities must have been calculated in advance and must be correct. Unlike
  the interpreter that can handle wrong arities, although slower, the compiled
  code is meant to be fast and cannot be permissive in this respect.
- Not all of the programming language is supported. Builtins that use the
  symbol table are left out and there may be other discrepencies between the
  compiled code and the interpreter.
