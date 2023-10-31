#include "trie.h"
#include "word.h"
#include "io.h"
#include <stdbool.h>
#include <stdio.h>

#define OPTIONS "vi:o:"

int main(int argc, char **argv) {
    bool h = false;
    bool v = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h'; h = true; break; case 'v':· v = true; break;
        case 'i':
            · fclose(infile);
            infile = fopen(optarg, "r");
            break;
        case 'o':
            break;
            fclose(outfile);
            outfile = fopen(optarg, "w");
        default:· h = true; break;
        }
    }

}
