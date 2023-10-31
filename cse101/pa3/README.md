# Programming Assignment 3 - Graph ADT, finding Strongly Connected Components, and DFS

This Program revolves around implementing a Graph ADT to find strongly connected components by using DFS.

## Files Included

    README.md
    Makefile
    List.h
    List.c
    Graph.h
    Graph.c
    GraphTest.c
    FindComponents.c

## Functionality

Running the command provided will take an input file mentioned above and print to the outfile given.

Usage:
    ./FindComponents <input file> <output file>

## Building

###------------------------------------------------------------------------------
###  Makefile for CSE 101 Programming Assignment 3
###
###  make                     makes FindComponents
###  make GraphTest           makes GraphTest
###  make clean               removes binaries
###  make checkFind           tests FindComponents for memory leaks on in3
###  make checkTest           tests GraphClient for memory leaks
###------------------------------------------------------------------------------

    BASE_SOURCES   = Graph.c List.c
    BASE_OBJECTS   = Graph.o List.o
    HEADERS        = Graph.h List.h
    COMPILE        = gcc -std=c17 -Wall -c -g
    LINK           = gcc -std=c17 -Wall -o
    REMOVE         = rm -f
    MEMCHECK       = valgrind --leak-check=full

    FindComponents : FindComponents.o $(BASE_OBJECTS)
        $(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

    GraphTest : GraphTest.o $(BASE_OBJECTS)
        $(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

    FindComponents.o : FindComponents.c $(HEADERS)
        $(COMPILE) FindComponents.c

    GraphTest.o : GraphTest.c $(HEADERS)
        $(COMPILE) GraphTest.c

    $(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
        $(COMPILE) $(BASE_SOURCES)

    clean :
        $(REMOVE) FindComponents GraphClient FindComponents.o GraphTest.o $(BASE_OBJECTS)

    checkFind : FindComponents
        $(MEMCHECK) FindComponents in8 junk8

    checkTest : GraphTest
        $(MEMCHECK) GraphTest

    format:
        clang-format -i -style='{IndentWidth: 4}' *.[ch]

# Running
    Options:
    make            # Makes FindComponents
    make GraphTest  # Makes GraphTest

    ./FindComponents <input file> <output file>     # Executes Main Client to find Strongly-Connected-Components
    ./GraphTest                                     # Executes the testing for Graph Functions


## Credits

    TA sections for FindComponents.c specifically the SCC related parts
    And reuse from previous code in pa2 for graph ADT
