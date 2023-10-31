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
