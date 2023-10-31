# Programming Assignment 7 - Dictionary ADT (BST) in cpp

This program revolves around implementing a Dictionary ADT that will essentially be used in our executable (Order.cpp) to assign a key value pair for each word in an infile.

## Files Included
    README.md
    Makefile
    Dictionary.h
    Dictionary.cpp
    DictionaryTest.cpp
    Order.cpp

## Functionality
    Running the command provided will write to an <outfile> a line by line ordering of a given input file of strings

    Usage ./Order <infile> <outfile>

## Building
    #------------------------------------------------------------------------------
    #  Makefile for CSE 101 Programming Assignment 7
    #
    #  make                     makes Order
    #  make DictionaryClient    makes DictionaryTest
    #  make clean               removes all binaries
    #  make OrderCheck          runs Order under valgrind on in5 junk5
    #  make DictionaryCheck     runs DictionaryClient under valgrind
    #------------------------------------------------------------------------------

    MAIN           = Order
    ADT            = Dictionary
    SOURCE         = $(MAIN).cpp
    OBJECT         = $(MAIN).o
    ADT_TEST       = $(ADT)Test
    ADT_SOURCE     = $(ADT).cpp
    ADT_OBJECT     = $(ADT).o
    ADT_HEADER     = $(ADT).h
    COMPILE        = g++ -std=c++17 -Wall -c
    LINK           = g++ -std=c++17 -Wall -o
    REMOVE         = rm -f
    MEMCHECK       = valgrind --leak-check=full

    $(MAIN): $(OBJECT) $(ADT_OBJECT)
    \···$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

    $(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
    \···$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

    $(OBJECT): $(SOURCE) $(ADT_HEADER)
    \···$(COMPILE) $(SOURCE)

    $(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
    \···$(COMPILE) $(ADT_TEST).cpp

    $(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
    \···$(COMPILE) $(ADT_SOURCE)

    clean:
    \···$(REMOVE) $(MAIN) $(ADT_TEST) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT)

    $(MAIN)Check: $(MAIN)
    \···$(MEMCHECK) $(MAIN) in5 junk5

    $(ADT)Check: $(ADT_TEST)
    \···$(MEMCHECK) $(ADT_TEST)

    format:
    \···clang-format -i -style='{IndentWidth: 4}' *.cpp

## Running
    Options:
    make                    # Makes Order
    make DictionaryTest     # Makes DictionaryTest

## Credits
    - Professor Tantalo for his psuedo-code
    - Previous assignments
    - TA sections
