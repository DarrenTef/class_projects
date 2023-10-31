/* Darren Lee, dlee181
 * CSE101 PA4, Spring 2023
 * MatrixTest.c
 * Test Client for testing Matrix ADT
 */

#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 3;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 3);
    changeEntry(A, 2, 1, 4);
    changeEntry(A, 2, 2, 5);
    changeEntry(A, 2, 3, 6);
    changeEntry(A, 3, 1, 7);
    changeEntry(A, 3, 2, 8);
    changeEntry(A, 3, 3, 9);

    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 3, 1);
    changeEntry(B, 3, 1, 1);
    changeEntry(B, 3, 2, 1);
    changeEntry(B, 3, 3, 1);

    Matrix C = copy(A);
    Matrix D = transpose(A);
    Matrix E = scalarMult(-1, A);
    Matrix F = scalarMult(10, A);

    Matrix P = product(A, B);
    Matrix PA = product(B, B);

    printf("\nA\n");
    printMatrix(stdout, A);
    printf("\nB\n");
    printMatrix(stdout, B);
    printf("\nCopy of A\n");
    printMatrix(stdout, C);
    printf("\ntranspose of A\n");
    printMatrix(stdout, D);
    printf("\nScalar -1 on A\n");
    printMatrix(stdout, E);
    printf("\nScalar 10 on A\n");
    printMatrix(stdout, F);
    Matrix S = sum(A, B);
    Matrix SA = sum(A, A);
    printf("\nsum of A and B\n");
    printMatrix(stdout, S);
    printf("Sum A+B NNZ: %d\n", NNZ(S));
    printf("\nsum of A and A\n");
    printMatrix(stdout, SA);
    printf("Sum A+A NNZ: %d\n", NNZ(SA));
    printf("\nB\n");
    printMatrix(stdout, B);
    printf("\n");
    Matrix Z = diff(B, A);
    Matrix ZA = diff(A, A);
    printf("\ndiff of B and A\n");
    printMatrix(stdout, Z);
    printf("\ndiff of A and A\n");
    printMatrix(stdout, ZA);

    printf("\nProduct A, B\n");
    printMatrix(stdout, P);
    printf("\n");
    printf("\nProduct B, B\n");
    printMatrix(stdout, PA);

    printf("\nEquals\n");
    printf("%d\n", equals(A, P));

    // NNZ()
    printf("\nNNZ()\n");
    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

    printf("%d\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

    // size()
    printf("%d\n", size(A));
    printMatrix(stdout, A);
    printf("\n");

    // makeZero()
    printf("makeZero()");
    printf("\n");
    makeZero(A);
    printMatrix(stdout, A);

    printf("%d\n", size(B));
    printMatrix(stdout, B);
    printf("\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&S);
    freeMatrix(&SA);
    freeMatrix(&Z);
    freeMatrix(&ZA);
    freeMatrix(&P);
    freeMatrix(&PA);

    return 0;
}
