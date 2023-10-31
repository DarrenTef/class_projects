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

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *prikey = fopen("ss.priv", "r");
    bool h = false;
    bool v = false;
    mpz_t d, pq;
    mpz_inits(d, pq, NULL);

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'n': prikey = fopen(optarg, "r"); break;
        case 'v': v = true; break;
        case 'h': h = true; break;
        default: h = true; break;
        }
    }

    if (prikey == NULL) {
        perror("Error with opening file: prikey\n");
    }

    // Read the private key from prikey
    ss_read_priv(pq, d, prikey);
    ss_decrypt_file(infile, outfile, d, pq);
    
    fclose(prikey);
    fclose(infile);
    // fclose(outfile);
    if (h) {
        fprintf(stderr, "Synopsis\n"
               "   Decrypts data using SS decryption.\n"
               "   Encrypted data is encrypted by the encrypt program.\n"
               "\n"
               "USAGE\n"
               "   ./decrypt [OPTIONS]\n"
               "\n"
               "OPTIONS\n"
               "   -h              Display program help and usage.\n"
               "   -v              Display verbose program output.\n"
               "   -i infile       Input file of data to decrypt (default: stdin).\n"
               "   -o outfile      Output file for decrypted data (default: stdout).\n"
               "   -n pvfile       Private key file (default: ss.priv).\n");
    } else {
        if (v) {
            gmp_fprintf(stderr, "pq (%d bits) = %Zd\n",mpz_sizeinbase(pq, 2), pq);
            gmp_fprintf(stderr,"d  (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
        }
    }

    // ss_decrypt_file(infile, outfile, d, pq);

    //fclose(prikey);
    //fclose(infile);
    fclose(outfile);
    //mpz_clears(d, pq, NULL);
    return 0;
}
