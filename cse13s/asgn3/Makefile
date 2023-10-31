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
	
