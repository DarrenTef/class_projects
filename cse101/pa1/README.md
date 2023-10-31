# Programming Assignment 1 - Doubly Linked Lists

This program revolves around building a Doubly Linked List ADT which essentially uses a List Struct and a Node struct. Using these functions we are able to use a indirect insertion sort alrgorithm which is implemented in Lex.c that allows us to Lexigraphically print into an output file from an input file.

## Functionality

Running the commands provided will take an input file and print the strings lexicographically sorted based on index into a provided output file. A List of commands bellow show the general synopsis for the executable.

Synopsis
    Takes an input file of strings, then lexicographically writes in the index of the strings into the provided output file.

    USAGE
    ./Lex <input file> <output file>

## Building

#------------------------------------------------------------------------------
 Makefile for CSE 101 Programming Assignment 1

 make                   makes Lex
 make ListClient        makes ListClient
 make clean             removes all binaries
 make checkClient       checks ListClient for memory errors
 make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

    Lex : Lex.o List.o
	    gcc -std=c17 -Wall -o Lex Lex.o List.o

    Lex.o : Lex.c List.h
	    gcc -std=c17 -Wall -c Lex.c

    ListTest: ListTest.o List.o
	    gcc -std=c17 -Wall -o ListTest ListTest.o List.o

    ListTest.o : ListTest.c List.h
	    gcc -std=c17 -Wall -c ListTest.c

    List.o : List.c List.h
	    gcc -std=c17 -Wall -c List.c

    clean :
	    rm -f Lex ListTest Lex.o ListTest.o List.o

    checkTest : 
	    valgrind --leak-check=full ListTest

    checkLex :
	    valgrind --leak-check=full Lex in3 blah3

# Running
    make Lex
    make ListTest
    ./ListTest                          # For Executing Test
    ./Lex <input file> <output file>    # For Executing Lex






