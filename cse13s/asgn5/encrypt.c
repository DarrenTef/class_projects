#include <stdio.h>
#include <gmp.h>
#include "numtheory.h"
#include <inttypes.h>
#include <stdlib.h>
#include "randstate.h"
#include "ss.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "i:o:n:vh"

// 17 Check if this is how you default to stdin
// 67 Should I be checking if input is stdin, and if so I shouldn't close it right

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pubkey = fopen("ss.pub", "r");
    bool h = false;
    bool v = false;
    mpz_t n;
    mpz_inits(n, NULL);

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': 
            fclose(infile);
            infile = fopen(optarg, "r"); break;
        case 'o': 
            fclose(outfile);
            outfile = fopen(optarg, "w"); break;
        case 'n': 
            fclose(pubkey);
            pubkey = fopen(optarg, "r"); break;
        case 'v': v = true; break;
        case 'h': h = true; break;
        default: h = true; break;
        }
    }

    if (pubkey == NULL) {
        perror("Error with opening file: pubkey\n");
    }

    // Read the public key from pubkey
    char username[256];
    ss_read_pub(n, username, pubkey);
    ss_encrypt_file(infile, outfile, n);
    fclose(pubkey);
    fclose(infile);
    // fclose(outfile);

    if (h) {
        fprintf(stderr, "Synopsis\n"
               "   Encrypts data using SS encryption.\n"
               "   Encrypted data is decrypted by the decrypt program.\n"
               "\n"
               "USAGE\n"
               "   ./encrypt [OPTIONS]\n"
               "\n"
               "OPTIONS\n"
               "   -h              Display program help and usage.\n"
               "   -v              Display verbose program output.\n"
               "   -i infile       Input file of data to encrypt (default: stdin).\n"
               "   -o outfile      Output file for encrypted data (default: stdout).\n"
               "   -n pbfile       Public key file (default: ss.pub).\n");
    } else {
        if (v) {
            gmp_fprintf(stderr ,"user = %s\n", username);
            gmp_fprintf(stderr, "public key n = %Zd\n", n);
        }
    }

    // ss_encrypt_file(infile, outfile, n);

    //fclose(pubkey);
    //fclose(infile);
    fclose(outfile);
    mpz_clears(n, NULL);
    return 0;
}
