// Contains main()

#include "universe.h"

#include <inttypes.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "htsn:i:o:"
#define DELAY   50000

int main(int argc, char **argv) {
    uint32_t rows = 0;
    uint32_t cols = 0;
    uint32_t n_gen = 100;
    bool toroidal = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *infilename;
    char *outfilename;
    bool print_syn = false;
    bool set_curse = true;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_syn = true; break;
        case 't': // Toroidal universe
            toroidal = true;
            break;
        case 's': set_curse = false; break;
        case 'n': n_gen = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'i': infilename = optarg; break;
        case 'o': outfilename = optarg; break;
        default: print_syn = true; break;
        }
    }

    if (infile != NULL) {
        fopen(infilename, "r");
    }
    if (outfile != NULL) {
        fopen(outfilename, "w");
    }

    fscanf(infile, "%" SCNu32 " %" SCNu32 " ", &rows, &cols); // Take first line
    Universe *A = uv_create(rows, cols, toroidal); // Create Toroidal Universe
    Universe *B = uv_create(rows, cols, toroidal);
    Universe *temp = A;
    uv_populate(A, infile);

    if (print_syn) {
        printf("SYNOPSIS\n Conway's Game of Life\n"
               "\n"
               "Usage\n"
               "\t./life_amd64 tsn:i:o:h\n"
               "\nOPTIONS\n"
               "   -t\tCreate your universe as a toroidal\n"
               "   -s\tSilent - do not use animate the evolution\n"
               "   -n {number}\tNumber of generations [default: 100]\n"
               "   -i {file}\tInput file [default: stdin]\n"
               "   -o {file}\tOutput File [default: stdout]\n");
    } else {

        if (set_curse) {
            initscr();
            curs_set(FALSE);
        }
        for (uint32_t i = 0; i < n_gen; i += 1) {
            if (set_curse) {
                clear();
            }
            for (uint32_t r = 0; r < uv_rows(A); r += 1) {
                for (uint32_t c = 0; c < uv_cols(A); c += 1) {
                    if (uv_get_cell(A, r, c)) {
                        if ((uv_census(A, r, c) == 2) || (uv_census(A, r, c) == 3)) {
                            uv_live_cell(B, r, c);
                        }
                    } else if (uv_get_cell(A, r, c) == false) {
                        if (uv_census(A, r, c) == 3) {
                            uv_live_cell(B, r, c);
                        }
                    } else {
                        uv_dead_cell(B, r, c);
                    }
                    if (uv_get_cell(A, r, c)) {
                        mvprintw(r, c, "o");
                    } else {
                        mvprintw(r, c, ".");
                    }
                }
            }
            temp = A;
	    A = B;
	    B = temp;
            refresh();
            usleep(DELAY);
        }
        if (set_curse) {
            endwin();
        }
    }


    uv_print(A, outfile);
    return 0;
}
