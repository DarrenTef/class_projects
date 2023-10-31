// My first ADT
//
// Questions What does Lying beyond the dimensions mean, ask for examples and a
// visualization fscanf("%u", &x, infile); //Reads an unsigned int from an
// infile

#include "universe.h"

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};
// Constructor
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = malloc(sizeof(Universe));
    bool **matrix = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t r = 0; r < rows; r += 1) {
        matrix[r] = (bool *) calloc(cols, sizeof(bool));
	u -> grid[r] = matrix[r];
    }
    u->cols = cols;
    u->rows = rows;
    u->toroidal = toroidal;
    return u;
}
void uv_delete(Universe *u) {
    for (uint32_t i = 0; i < u->rows; i += 1) {
        free(u->grid[i]);
        u->grid[i] = NULL;
    }
    free(u->grid);
    u->grid = NULL;
}

uint32_t uv_rows(Universe *u) {
    return u->rows;
}

uint32_t uv_cols(Universe *u) {
    return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    if ((r > u->rows) || (c > u->cols) || c < 0 || r < 0) { // out of bound
        return;
    } else {
        u->grid[r][c] = true;
    }
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    u->grid[r][c] = false;
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if ((r > u->rows) || (c > u->cols) || c < 0 || r < 0) {
        return false;
    } else {
        return true;
    }
}

bool uv_populate(Universe *u, FILE *infile) {
    uint32_t x = 0;
    uint32_t y = 0;
    while (!feof(infile)) {
        fscanf(infile, "%" SCNu32 " %" SCNu32, &x, &y);
        if (((x >= u->rows) || (y >= u->cols) || x < 0 || y < 0)) {
            fprintf(stderr, "Malformed input");
            return false;
        }
        u->grid[x][y] = true;
    }
    return true;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) { // returns the number of neighbors
    uint32_t n = 0;
    uint32_t n_t = 0;
    int32_t dx[4] = { -1, 0, 1, 0 };
    int32_t dy[4] = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; i += 1) {
        uint32_t r_new = (r + dx[i] + u->rows) % u->rows;
        uint32_t c_new = (c + dy[i] + u->cols) % u->cols;
        if (u->toroidal) {
            if (uv_get_cell(u, r_new, c_new)) {
                n_t += 1;
            }
        } else {
            if (uv_get_cell(u, r_new, c_new)
                && ((r > u->rows) || (c > u->cols) || c < 0 || r < 0)) {
                n += 1;
            }
        }
    }
    if (u->toroidal) {
        return n_t;
    }
    return n;
}

void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t r = 0; r < u->rows; r += 1) {
        for (uint32_t c = 0; c < u->cols; c += 1) {
            if (uv_get_cell(u, r, c)) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
    }
}
