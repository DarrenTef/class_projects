# Assignment 1 - monte carlo estimation of pi

The use of Monte Carlo's estimation of pi to generate plots relating to the ratio of a square and a quadrant of a circle and the estimation compared to pi in the form of error.

## Building
```
SHELL := /bin/sh 
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: monte_carlo

monte_carlo: monte_carlo.o
        $(CC) -o monte_carlo monte_carlo.o

monte_carlo.o: monte_carlo.c
        $(CC) $(CFLAGS) -c monte_carlo.c
clean:
        rm -f monte_carlo

format:
        clang-format -i -style=file *.[ch]
```
## Running
```
$ ./plot.sh
```                   
