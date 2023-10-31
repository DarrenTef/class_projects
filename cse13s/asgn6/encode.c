#include "trie.h"
#include "word.h"
#include "io.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#define OPTIONS "vi:o:"

int main(int argc, char **argv) {
    bool h = false;
    bool v = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h'; h = true; break; case 'v': v = true; break;
        case 'i':
            fclose(infile);
            infile = fopen(optarg, "r");
            break;
        case 'o':
            break;
            fclose(outfile);
            outfile = fopen(optarg, "w");
        default: h = true; break;
        }
    }
    

    if (infile == NULL) {
        perror("Error with opening file: infile\n");
    }
    if (outfile == NULL) { 
        perror("Error with opening file: outfile\n");
    }

    int fd = fileno(infile);



    if (h) {
        fprintf(stderr, "SYNOPSIS\n"
                        "   Compresses files using the LZ78 compression algorithm.\n"
                        "   Compressed files are decompressed with the corresponding decoder.\n"
                        "\n"
                        "USAGE\n"
                        "   ./encode [-vh] [-i input] [-o output]\n"
                        "\n"
                        "OPTIONS\n"
                        "   -v          Display compression statistics\n"
                        "   -i input    Specify input to compress (stdin by default)\n"
                        "   -o output   Specify output of compressed input (stdout by default)\n"
                        "   -h          Display program help and usage\n");
    } else {
        if (v) {
            // Print verbose data
        }
    }
