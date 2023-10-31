C		= clang
CFLAGS	= -Wall -Wpedantic -Werror -Wextra
LDFLAGS	= 
EXEC 	= 
OBJS	= io.c

all: $(EXEC)

$(EXEC): % : %.o $(OBJS)
		$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
		$(CC) $(CFLAGS) -c $<

clean:
		rm -f $(EXEC) $(OBJS)

debug: CFLAGS += -g -gdwarf-4
format:
		clang-format -i -style=file *.[ch]

scan-build: clean
		scan-build --use-cc=$(CC) make



