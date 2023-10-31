# Programming Assignment 5 - List ADT in cpp

This program revolves around implementing a List ADT that will ultimately be used to do a set of shuffling opperations on a List of cards.

## Files Included
    ListTest.cpp
    List.cpp
    List.h
    Shuffle.cpp
    README.md
    Makefile

## Functionality

Running the command provided will write to stdout a set of cards and the amount of shuffles it takes to recreate the original deck

    Usage:
        ./Shuffle <int>

## Building

    #------------------------------------------------------------------------------
    #  Makefile for List ADT
    #
    #  make                makes Shuffle
    #  make ListTest \··   make ListTest
    #  make clean          removes binary files
    #  make check1         runs valgrind on ListTest
    #  make check2         runs valgrind on Shuffle with CLA 35
    #------------------------------------------------------------------------------

    Shuffle : Shuffle.o List.o
    \···g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o

    Shuffle.o : List.h Shuffle.cpp
    \···g++ -std=c++17 -Wall -c Shuffle.cpp

    ListTest : ListTest.o List.o
    \···g++ -std=c++17 -Wall -o ListTest ListTest.o List.o

    ListTest.o : List.h ListTest.cpp
    \···g++ -std=c++17 -Wall -g -c ListTest.cpp

    List.o : List.h List.cpp
    \···g++ -std=c++17 -Wall -c List.cpp

    clean :
    \···rm -f Shuffle Shuffle.o ListTest ListTest.o List.o

    check1 : ListTest
    \···valgrind --leak-check=full ListTest

    check2 : Shuffle
    \···valgrind --leak-check=full Shuffle 35

    format:
    \···clang-format -i -style='{IndentWidth: 4}' *.[ch]

# Running
    Options:
    make                    # Makes Shuffle
    make ListTest           # Makes ListTest

## Credits

    TA sections for helping with functions of List ADT
