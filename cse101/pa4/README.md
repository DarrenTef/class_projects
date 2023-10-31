# Programming Assignment 4 - Matrix ADT, creating a sparse matrix and doing matrix operations on these sparse matrix

This Program revolves around implementing a Matrix ADT that will create a sparse Matrix, which we then use to add, subtract, transpose, scalarMultiply, and take the product of two matrices.

## Files Included

    Sparce.c
    Matrix.c
    Matrix.h
    MatrixTest.c
    List.c
    List.h
    ListTest.c
    README.md
    Makefile

## Functionality

Running the command provided will take input file mentioned above and print to the outfile given.

Usage:
    ./Sparse <input file> <output file>

## Building

###------------------------------------------------------------------------------
###  Makefile for CSE 101 Programming Assignment 4
###
###  make                     makes Sparse
###  make MatrixTest          makes MatrixTest
###  make ListTest            makes ListTest
###  make clean               removes all binaries
###  make SparseCheck         runs Sparse in valgrind on in5
###  make MatrixCheck         runs MatrixTest in valgrind
###  make ListCheck           runs ListTest in valgrind
###------------------------------------------------------------------------------

    MAIN           = Sparse
    ADT1           = Matrix
    ADT2           = List
    SOURCE         = $(MAIN).c
    OBJECT         = $(MAIN).o
    ADT1_TEST      = $(ADT1)Test
    ADT1_SOURCE    = $(ADT1).c
    ADT1_OBJECT    = $(ADT1).o
    ADT1_HEADER    = $(ADT1).h
    ADT2_TEST      = $(ADT2)Test
    ADT2_SOURCE    = $(ADT2).c
    ADT2_OBJECT    = $(ADT2).o
    ADT2_HEADER    = $(ADT2).h
    COMPILE        = gcc -std=c17 -Wall -g -c
    LINK           = gcc -std=c17 -Wall -o
    REMOVE         = rm -f
    MEMCHECK       = valgrind --leak-check=full

    $(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
        $(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

    $(ADT1_TEST): $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)
        $(LINK) $(ADT1_TEST) $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

    $(ADT2_TEST): $(ADT2_TEST).o $(ADT2_OBJECT)
        $(LINK) $(ADT2_TEST) $(ADT2_TEST).o $(ADT2_OBJECT)

    $(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
        $(COMPILE) $(SOURCE)

    $(ADT1_TEST).o: $(ADT1_TEST).c $(ADT1_HEADER) $(ADT2_HEADER)
        $(COMPILE) $(ADT1_TEST).c

    $(ADT2_TEST).o: $(ADT2_TEST).c $(ADT2_HEADER)
        $(COMPILE) $(ADT2_TEST).c

    $(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
        $(COMPILE) $(ADT1_SOURCE)

    $(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
        $(COMPILE) $(ADT2_SOURCE)

    clean:
        $(REMOVE) $(MAIN) $(ADT1_TEST) $(ADT2_TEST)
        $(REMOVE) $(OBJECT) $(ADT1_TEST).o $(ADT2_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

    $(MAIN)Check: $(MAIN)
        $(MEMCHECK) $(MAIN) in5 junk5

    $(ADT1)Check: $(ADT1_TEST)
        $(MEMCHECK) $(ADT1_TEST)

    $(ADT2)Check: $(ADT2_TEST)
        $(MEMCHECK) $(ADT2_TEST)

    format:
        clang-format -i -style='{IndentWidth: 4}' *.[ch]

# Running
    Options:
    make                    # Makes Sparse.c
    make MatrixTest         # Makes MatrixTest.c
    make ListTest           # Makes ListTest.c

## Credits

    TA sections for functions within Matrix.c
    Reuse of code from Pa2 for List ADT





