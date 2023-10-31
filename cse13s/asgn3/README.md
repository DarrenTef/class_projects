# Assignment 3 - Algorithms are Everything

This program revolves around the ability to parse arguments which get turned into members of a set that is 32 bits long. This set then triggers function calls to multiple different sorting algorithms which ultimately allow for different amount of moves and compares. These values show the difference in each implementation from quick, shell, batcher, and heap. Each value will be less than 2 to the 30 so about a billion large.

## Functionality

Running the command provided will print different things
Here is a list of the number of commands and their print statments:
   -H :		Display program help and usage.
   -a : 	Enable all sorts.
   -s : 	Enable Shell sort.
   -b : 	Enable Batcher sort.
   -h : 	Enable Heap sort.
   -q : 	Enable Quick sort.
   -n length: 	Specify number of array elements (defaults: 100).
   -p elements:	Specify random seed (default: 13371453).

## Building

```

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -Ofast -g -gdwarf-4
LDFLAGS  =  -lm
EXEC = sorting 
OBJS = sorting.o shell.o stats.o heap.o quick.o batcher.o set.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(OBJS)

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make
```

## Running
```
./mathlib-test [-Habhqn:p:s:]
```
