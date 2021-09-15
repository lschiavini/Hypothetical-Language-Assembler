# Hypothetical-Language-Assembler

## Summary:

Assembler for simple assembly language with educational purposes. It uses a 14 instruction table. This assembler uses onepass algorithm.

### Table of supported operations

<p align="center">
  <img  src="https://github.com/lschiavini/Hypothetical-Language-Assembler/blob/master/docs/instructionsTable.png">
</p>

## Project Structure:
```
├── README.md (This file)
├── /docs
│ └── trabalho1.pdf (Specifications in portuguese)
├── /tests/ (holds all .asm files as results)
├── /src/
|     └── main.cpp (principal code of the project)
|     └── utils.cpp (utils for dealing with files)
|     └── /includes/ (libraries headers directory)
|     |    └── utils.h (refer to utils.cpp)
|     └── /lib/ (libraries source code directory)
|          └── /args/ (lib for dealing with bash arguments)
|          |    └── /include/args.h
|          |              └── /src/args.cpp
|          |              └── CMakeLists.txt (Cmake build configurations for args)
|          └── /assembler/ (actual assembler lib)
|                    └── /include
|                    |       └── assembler.h
|                    |       └── stringUtils.h
|                    |       └── symbolTable.h
|                    └── /src
|                    |       └── assembler.cpp (Assembler with onepass algorithm)
|                    |       └── stringUtils.cpp (deals with common string uses)
|                    |       └── symbolTable.cpp (operates on symbolTable of usedVales)
|                    └── CMakeLists.txt (Cmake build configurations for assembler)
├── CMakeLists.txt (Cmake build configurations)
├── build.sh (building script)
├── buildAndRun.sh (builds and runs default /tests/binDataLast.asm)
```
## Environment:

OS: Linux
gcc: version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04
cmake: version 3.16.3

## How to Run:

To build and run with binDataLast.asm:

> chmod -x buildAndRun.sh

To build and run with other files:

> chmod -x build.sh

>sh build.sh

>./bin/assemblerMain 'NAMEOFFILE'.asm

OutPut Files :
 - Either errors inline or
 - /tests/'NAMEOFFILE'.obj (the object binary code of the input file)



