# Programming Assignment 2 - Graph ADT and BFS

This Program Revolves around building a Graph ADT which implemented BFS. Using this ADT we allow the Client program to find the shortest paths between pairs of vertices.
The Client program will take an input file of a source, vertices, and distances and display them in the form of an adjacency list and readable distances in the outfile.

## Files Included

    List.c
    List.h
    Graph.c
    Graph.h
    GraphTest.c
    FindPath.c
    Makefile
    README.md

## Functionality

Running the command provided will take an input file mentioned above and print to the outfile given.

Usage:

    ./FindPath <input file> <output file>

## Building

###  Makefile for CSE 101 Programming Assignment 2
### ------------------------------------------------------------------------------
###  make                     makes FindPath
###  make GraphTest           makes GraphTest
###  make clean               removes binaries
###  make checkFind           tests FindPath for memory leaks on in7
###  make checkTest           tests GraphTest for memory leaks
### ------------------------------------------------------------------------------

    BASE_SOURCES   = Graph.c List.c
    BASE_OBJECTS   = Graph.o List.o
    HEADERS        = Graph.h List.h
    COMPILE        = gcc -std=c17 -Wall -g -c
    LINK           = gcc -std=c17 -Wall -o
    REMOVE         = rm -f
    MEMCHECK       = valgrind --leak-check=full

    FindPath : FindPath.o $(BASE_OBJECTS)
    \···$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

    GraphTest : GraphTest.o $(BASE_OBJECTS)
    \···$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

    FindPath.o : FindPath.c $(HEADERS)
    \···$(COMPILE) FindPath.c

    GraphTest.o : GraphTest.c $(HEADERS)
    \···$(COMPILE) GraphTest.c

    $(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
    \···$(COMPILE) $(BASE_SOURCES)

    clean :
    \···$(REMOVE) FindPath FindPath.o GraphTest.o GraphTest $(BASE_OBJECTS)

    checkFind : FindPath
    \···$(MEMCHECK) FindPath in7 junk7

    checkTest : GraphTest
    \···$(MEMCHECK) GraphTest

# Running
    Options:
    make FindPath
    make GraphTest
    ./FindPath <input file> <output file>   # Executes Main Client to Find Shortest Path
    ./GraphTest                             # Executes Testing for Graph Functions


