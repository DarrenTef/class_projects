CC 	= clang
CFLAGS 	= -Wall -Wpedantic -Werror -Wextra -Ofast
LDFLAGS	= -lncurses 
EXEC 	= life
OBJS 	= life.o universe.o 

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -g -gdwarf-4 -c $<

clean:
	rm -f $(EXEC) $(OBJS)

format:
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build --use-cc=$(CC) make
			
			
