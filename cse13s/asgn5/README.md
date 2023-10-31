# Assignment 5 - MPZ Library and a tiny bit of Encryption

This program revolves around creating public and private keys, encrypting a message, and then decrypting the cypher text produced by the encrypter inorder to securely send information between users. This program also contains multiple encryption related math functions which give us the capability to manipulate extremely large integers.

## Functionality

Running the commands provided will print and generate different things. A list of list of commands bellow show the general synopsis for each exectuable:

SYNOPSIS
   Generates an SS public/private key pair.

   USAGE
      ./keygen [OPTIONS]

      OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -b bits         Minimum bits needed for public key n (default: 256).
   -i iterations   Miller-Rabin iterations for testing primes (default: 50).
   -n pbfile       Public key file (default: ss.pub).
   -d pvfile       Private key file (default: ss.priv).
   -s seed         Random seed for testing.


SYNOPSIS
	Decrypts data using SS decryption.
	Encrypted data is encrypted by the encrypt program.

USAGE
	./decrypt [OPTIONS]

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to decrypt (default: stdin).
   -o outfile      Output file for decrypted data (default: stdout).
   -n pvfile       Private key file (default: ss.priv).

USAGE
   ./encrypt [OPTIONS]

OPTIONS
   -h              Display program help and usage.
   -v              Display verbose program output.
   -i infile       Input file of data to encrypt (default: stdin).
   -o outfile      Output file for encrypted data (default: stdout).
   -n pbfile       Public key file (default: ss.pub).

## Building

CC      = clang
CFLAGS  = -Wall -Wpedantic -Werror -Wextra
LDFLAGS = `pkg-config --libs gmp`
EXEC    = keygen encrypt decrypt
OBJS    = numtheory.o randstate.o ss.o

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

To build simply type 'make' into terminal and it will compile the code, if you want to clean type make clean, and to make everything type make all.


# Running

./keygen [b:i:n:d:s:vh]
./encrypt [i:o:n:vh]
./decrypt [i:o:n:vh]


Give the command echo [text to be encrypted] | ./encrypt | ./decrypt
The '|' essentially pipes the stdout and uses it as the input for the thing it is piping into.











