Soy
---

Build|Linux|Windows|Coverity
---|---|---|---
status|[![GitHub CI build status](https://github.com/Wodan58/Soy/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/Wodan58/Soy/actions/workflows/c-cpp.yml)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Soy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Soy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/22425.svg)](https://scan.coverity.com/projects/wodan58-duplo)

This repository contains runtime files for programs that have been translated
by [Moy](https://github.com/Wodan58/Moy) into C. This project also depends on
the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Build instructions
------------------

    make

Changes
-------

Some builtins are not supported because they have no business in compiled code.
