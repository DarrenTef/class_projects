# Assignment 2 - A Slice of Pi

This program revolves around the ability to parse arguments which will return multiple implementations of the approximations of pi, and implementation of euler's number, and newton's square root, which we ended using to compare to the math.h library's version and found the difference. This program also prints out the desired number of iterations it took before our approximations were deemed "sufficient".

## Functionality

Running the command provided will print different things
Here is a list of the commands and their print statements:
-a : Runs all tests.
-e : Runs e(Euler's number) approximation test.
-b : Runs Bailey-Borwein-Plouffe approximation test (pi).
-m : Runs Madhava pi approximation.
-r : Runs Euler sequence (test for pi).
-v : Runs Viete pi approximation test.
-n : Runs Newton-Raphson square root approximation tests (From [0:10) with steps of 0.1).
-s : Prints statistics to see how many terms and factors it took for each implementation to reach a satisfactory approximation.
-h : Displays the help message (A synopsis).
Invalid Flags : Will display the help message.

## Building

```
CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra -Ofast 
LDFLAGS  =  -lm 
EXEC = mathlib-test
OBJS = madhava.o mathlib-test.o bbp.o newton.o e.o euler.o viete.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXEC) $(OBJS)

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
./mathlib-test [-aebmrvnsh]
```

