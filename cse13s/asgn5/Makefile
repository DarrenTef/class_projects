CC	= clang
CFLAGS	= -Wall -Wpedantic -Werror -Wextra
LDFLAGS	= `pkg-config --libs gmp`
EXEC 	= keygen encrypt decrypt
OBJS	= numtheory.o randstate.o ss.o

all: $(EXEC)

$(EXEC): % : %.o $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -g -gdwarf-4 -c $<

clean:
	rm -f $(EXEC) $(OBJS)

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make


