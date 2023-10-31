# Programming Assignment 6 - Big Integer ADT in cpp

This program revolves around implementing a Big Integer ADT that will essentially compute basic mathmatical operations on extremely large numbers in cpp which we will print to and outfile from infile using our Arithmetic client.

## Files Included
    Arithmetic.cpp
    BigInteger.cpp
    BigInteger.h
    BigIntegerTest.cpp
    List.cpp
    List.h
    ListTest.cpp
    Makefile
    README.md

## Functionality

    Running the command provided will write to an <outfile> a set of operations on two big integers specified on an <infile>

    Usage ./Arithmetic <infile> <outfile>

## Building

    #------------------------------------------------------------------------------
    #  Makefile for CSE 101 Programming Assignment 6
    #
    #  make                     makes Arithmetic
    #  make BigIntegerClient    makes BigIntegerClient
    #  make ListClient          makes ListClient
    #  make clean               removes all binaries
    #  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
    #  make BigIntegerCheck     runs BigIntegerTest in valgrind
    #  make ListCheck           runs ListTest in valgrind
    #------------------------------------------------------------------------------

    MAIN           = Arithmetic
    ADT1           = BigInteger
    ADT2           = List
    SOURCE         = $(MAIN).cpp
    OBJECT         = $(MAIN).o
    ADT1_TEST      = $(ADT1)Test
    ADT1_SOURCE    = $(ADT1).cpp
    ADT1_OBJECT    = $(ADT1).o
    ADT1_HEADER    = $(ADT1).h
    ADT2_TEST      = $(ADT2)Test
    ADT2_SOURCE    = $(ADT2).cpp
    ADT2_OBJECT    = $(ADT2).o
    ADT2_HEADER    = $(ADT2).h
    COMPILE        = g++ -std=c++17 -Wall -g -c
    LINK           = g++ -std=c++17 -Wall -o
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

    $(ADT1_TEST).o: $(ADT1_TEST).cpp $(ADT1_HEADER) $(ADT2_HEADER)
        $(COMPILE) $(ADT1_TEST).cpp

    $(ADT2_TEST).o: $(ADT2_TEST).cpp $(ADT2_HEADER)
        $(COMPILE) $(ADT2_TEST).cpp

    $(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
        $(COMPILE) $(ADT1_SOURCE)

    $(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
        $(COMPILE) $(ADT2_SOURCE)

    clean:
        $(REMOVE) $(MAIN) $(ADT1_TEST) $(ADT2_TEST)
        $(REMOVE) $(OBJECT) $(ADT1_TEST).o $(ADT2_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

    $(MAIN)Check: $(MAIN)
        $(MEMCHECK) $(MAIN) in4 junk4

    $(ADT1)Check: $(ADT1_TEST)
        $(MEMCHECK) $(ADT1_TEST)

    $(ADT2)Check: $(ADT2_TEST)
        $(MEMCHECK) $(ADT2_TEST)

    format:
        clang-format -i -style='{IndentWidth: 4}' *.[ch]

## Running
    Options:
    make                    # Makes Arithmetic
    make ListTest           # Makes ListTest
    make BigIntegerTest     # Makes BigIntegerTest

## Credits

    Ta Sections for helping with BigInteger ADT functions like normalize






