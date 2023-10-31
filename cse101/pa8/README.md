# Programming Assignment 8 - Dictionary ADT (RBT) in cpp

This program revolves around implementing a RBT Dictionary ADT that will essentially be used in our executable (Order.cpp) to assign a key value pair for each word in an infile.
It will also be used in our other executable (WordFrequency.cpp) which will essentially gather up duplicate keys and instead it will incrememnt each key's value if there are duplicates.

## Files Included
    README.md
    Makefile
    Dictionary.h
    Dictionary.cpp
    DictionaryTest.cpp
    Order.cpp
    WordFrequency.cpp

## Functionality
    Running the command provided will write to an <outfile> a line by line ordering of a given input file of strings

    Usage
    ./Order <infile> <outfile>
    ./WordFrequency <infile> <outfile>

## Building
    #------------------------------------------------------------------------------
    #  Makefile for CSE 101 Programming Assignment 8
    #
    #  make                     makes WordFrequency and Order
    #  make DictionaryTest    makes DictionaryTest
    #  make clean               removes all binaries
    #  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
    #  make DictionaryCheck     runs DictionaryClient under valgrind
    #------------------------------------------------------------------------------
    all : Order WordFrequency

    Order : Order.o Dictionary.o
    \···g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

    Order.o : Dictionary.h Order.cpp
    \···g++ -std=c++17 -Wall -c Order.cpp

    WordFrequency : WordFrequency.o Dictionary.o
    \···g++ -std=c++17 -Wall -o WordFrequency WordFrequency.o Dictionary.o

    WordFrequency.o : Dictionary.h WordFrequency.cpp
    \···g++ -std=c++17 -Wall -c WordFrequency.cpp

    DictionaryTest : DictionaryTest.o Dictionary.o
    \···g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o

    DictionaryTest.o : Dictionary.h DictionaryTest.cpp
    \···g++ -std=c++17 -Wall -c DictionaryTest.cpp

    Dictionary.o : Dictionary.h Dictionary.cpp
    \···g++ -std=c++17 -Wall -c Dictionary.cpp

    clean :
    \···rm -f Order Order.o WordFrequency WordFrequency.o DictionaryTest DictionaryTest.o Dictionary.o

    check1 : DictionaryTest
    \···valgrind --leak-check=full DictionaryTest

    check2 : Order
    \···valgrind --leak-check=full Order in5 junk5

    check3 : WordFrequency
    \···valgrind --leak-check=full WordFrequency GutenBerg.txt


## Running
    Options:
    make                    # Makes Order and WordFrequency
    make DictionaryTest     # Makes DictionaryTest

## Credits
    - Professor Tantalo for his psuedo-code
    - Previous assignments
    - TA sections

