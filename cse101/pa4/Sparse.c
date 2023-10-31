/* Darren Lee, dlee181
 * CSE101 PA4, Spring 2023
 * Sparce.c
 * Executable Client file which utilizes List ADT and Matrix ADT
 */

#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *infile, *outfile;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Unable to open %s <input> file\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fprintf(stderr, "Unable to open %s <outfile> file\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Check if argc is greater than two
    if (infile == NULL) {
        fprintf(stderr, "Lex.c Error, could not open infile, NULL");
        exit(EXIT_FAILURE);
    }
    // n is the dimensions of both the matrixes
    int n, a, b;
    fscanf(infile, "%d %d %d", &n, &a, &b);
    fscanf(infile, "\n");
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    int row, col;
    double val;

    for (int i = 0; i < a; i += 1) {
        fscanf(infile, "%d %d %lf", &row, &col, &val);
        changeEntry(A, row, col, val);
    }

    for (int i = 0; i < b; i += 1) {
        fscanf(infile, "%d %d %lf", &row, &col, &val);
        changeEntry(B, row, col, val);
    }
    Matrix scalar, sumab, sumaa, difba, difaa, transa, prodab, prodbb;
    fprintf(outfile, "A has %d non-zero entries:\n", a);
    printMatrix(outfile, A);
    fprintf(outfile, "\nB has %d non-zero entries:\n", b);
    printMatrix(outfile, B);

    fprintf(outfile, "\n(1.5)*A =\n");
    scalar = scalarMult(1.5, A);
    printMatrix(outfile, scalar);

    fprintf(outfile, "\nA+B =\n");
    sumab = sum(A, B);
    printMatrix(outfile, sumab);

    fprintf(outfile, "\nA+A =\n");
    sumaa = sum(A, A);
    printMatrix(outfile, sumaa);

    fprintf(outfile, "\nB-A =\n");
    difba = diff(B, A);
    printMatrix(outfile, difba);

    fprintf(outfile, "\nA-A =\n");
    difaa = diff(A, A);
    printMatrix(outfile, difaa);

    fprintf(outfile, "\nTranspose(A) =\n");
    transa = transpose(A);
    printMatrix(outfile, transa);

    fprintf(outfile, "\nA*B =\n");
    prodab = product(A, B);
    printMatrix(outfile, prodab);

    fprintf(outfile, "\nB*B =\n");
    prodbb = product(B, B);
    printMatrix(outfile, prodbb);
    fprintf(outfile, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalar);
    freeMatrix(&sumaa);
    freeMatrix(&sumab);
    freeMatrix(&difba);
    freeMatrix(&difaa);
    freeMatrix(&transa);
    freeMatrix(&prodab);
    freeMatrix(&prodbb);

    fclose(infile);
    fclose(outfile);
    return 0;
}
