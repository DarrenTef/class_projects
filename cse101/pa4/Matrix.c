/*
 * Darren Lee, dlee181
 * CSE101 PA4, Spring 2023
 * Matrix.c
 * Matrix ADT
 */

#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    List *entries;
    int row;
    int nnz;

} MatrixObj;

typedef struct EntryObj *Entry;

// Helper --------------------------------------
void freeEntry(Entry *e) {
    if (e == NULL) {
        fprintf(stderr, "Cant free NULL entry in free");
        exit(EXIT_FAILURE);
    }
    free(*e);
    e = NULL;
}
// CONSTRUCTORS / DESTRUCTOR --------------------
Entry newEntry(int col, double val) {
    if (col < 0) {
        fprintf(stderr, "Matrix does not exist in newEntry, column < 0");
        exit(EXIT_FAILURE);
    }
    Entry e = malloc(sizeof(EntryObj));
    if (e == NULL) {
        fprintf(stderr, "e == NULL in newEntry");
        exit(EXIT_FAILURE);
    }
    e->column = col;
    e->value = val;
    return e;
}

Matrix newMatrix(int n) {
    if (n <= 0) {
        fprintf(stderr, "Cannot have a matrix with n <= 0");
        exit(EXIT_FAILURE);
    }
    Matrix m = malloc(sizeof(MatrixObj));
    if (m == NULL) {
        fprintf(stderr, "Matrix does not exist in newMatrix, m == NULL");
        exit(EXIT_FAILURE);
    }
    m->entries = malloc((n + 1) * sizeof(List));
    if (m->entries == NULL) {
        fprintf(stderr, "m->entries == NULL in newMatrix");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < n + 1; i += 1) {
        m->entries[i] = newList();
    }

    m->row = n;
    m->nnz = 0;
    return m;
}

void freeMatrix(Matrix *pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= ((*pM)->row); i += 1) {
            for (moveFront((*pM)->entries[i]); index((*pM)->entries[i]) != -1;
                 moveNext((*pM)->entries[i])) {
                Entry e = get((*pM)->entries[i]);
                freeEntry(&e);
            }
            freeList(&(*pM)->entries[i]);
        }
        free((*pM)->entries);
        free(*pM);
        *pM = NULL;
    }
}

// ACCESSORS ------------------------------------
int size(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "M == NULL, in size()");
        exit(EXIT_FAILURE);
    }
    return M->row;
}

int NNZ(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "M == NULL, in NNZ()");
        exit(EXIT_FAILURE);
    }
    return M->nnz;
}

int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "A || B are null in equals()");
        exit(EXIT_FAILURE);
    }
    if (NNZ(A) != NNZ(B)) {
        return false;
    }
    bool eq;
    Entry X, Y;
    eq = (size(A) == size(B));
    for (int i = 1; i <= size(A); i += 1) {
        moveFront(A->entries[i]);
        moveFront(B->entries[i]);
        while (eq && index(A->entries[i]) != -1 && index(B->entries[i]) != -1) {
            X = get(A->entries[i]);
            Y = get(B->entries[i]);
            if (length(A->entries[i]) == length(B->entries[i])) {
                eq = (X->value == Y->value);
                moveNext(B->entries[i]);
                moveNext(A->entries[i]);
            } else {
                return false;
            }
        }
    }
    return eq;
}

// SETTERS --------------------------------------
void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "M is NULL in makeZero");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i += 1) {
        moveFront(M->entries[i]);
        while (index(M->entries[i]) != -1) {
            Entry e = get(M->entries[i]);
            freeEntry(&e);
            moveNext(M->entries[i]);
        }
        clear(M->entries[i]);
    }
    M->nnz = 0;
}

// i = Rows, j = Col
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "M == NULL in changeEntry()");
        exit(EXIT_FAILURE);
    }
    if (i <= 0 || i > size(M)) {
        fprintf(stderr, "i <= 0 in || i > size(M) changeEntry()");
        exit(EXIT_FAILURE);
    }
    if (j <= 0 || j > size(M)) {
        fprintf(stderr, "j <= 0 || j > size(M) in changeEntry()");
        exit(EXIT_FAILURE);
    }
    if (length(M->entries[i]) > 0) {
        moveBack(M->entries[i]);
        while ((index(M->entries[i]) != -1)) {
            Entry ecol = get(M->entries[i]);
            if (j > ecol->column) {
                if (x != 0) {
                    Entry ee = newEntry(j, x);
                    insertAfter(M->entries[i], ee);
                    M->nnz += 1;
                }
                break;
            } else if (j == ecol->column) {
                if (x == 0) {
                    Entry el = get(M->entries[i]);
                    freeEntry(&el);
                    delete (M->entries[i]);
                    M->nnz -= 1;
                    return;
                } else {
                    Entry ex = get(M->entries[i]);
                    ex->column = j;
                    ex->value = x;
                }
                break;
            } else {
                movePrev(M->entries[i]);
            }
        }

        if ((index(M->entries[i]) == -1) && x != 0) {
            Entry eee = newEntry(j, x);
            prepend(M->entries[i], eee);
            M->nnz += 1;
        }
    } else {
        if (x != 0) {
            Entry e = newEntry(j, x);
            append(M->entries[i], e);
            M->nnz += 1;
        }
    }
}

// MATRIX ARITHMETIC OPERTATIONS ----------------
// returns a reference to a new MatrixObj having the same entries as A
Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "A == NULL in copy()");
        exit(EXIT_FAILURE);
    }
    Matrix cpy = newMatrix(size(A));
    for (int i = 1; i <= size(A); i += 1) {
        if (length(A->entries[i]) > 0) {
            moveFront(A->entries[i]);
            while (index(A->entries[i]) != -1) {
                Entry e = get(A->entries[i]);
                changeEntry(cpy, i, e->column, e->value);
                moveNext(A->entries[i]);
            }
        }
    }
    return cpy;
}

Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "A == NULL in transpose()");
        exit(EXIT_FAILURE);
    }
    Matrix t = newMatrix(size(A));
    List L;
    for (int i = 1; i <= size(A); i += 1) {
        L = A->entries[i];
        moveFront(L);
        while (index(L) != -1) {
            // printf("transp\n");
            Entry e = get(L);
            changeEntry(t, e->column, i, e->value);
            moveNext(L);
        }
    }
    return t;
}

Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "A == NULL in scalarMult()");
        exit(EXIT_FAILURE);
    }
    Matrix M = copy(A);
    for (int i = 1; i <= size(M); i += 1) {
        if (length(A->entries[i]) > 0) {
            moveFront(M->entries[i]);
            while (index(M->entries[i]) != -1) {
                // Entry e = get(M->entries[i]);
                ((Entry)get(M->entries[i]))->value *= x;
                moveNext(M->entries[i]);
            }
        }
    }
    return M;
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "A || B == NULL in sum()");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "size(A) != size(B) in sum()");
        exit(EXIT_FAILURE);
    }
    Matrix S = newMatrix(size(A));
    bool eq = false;
    if (A == B) {
        eq = true;
    }
    for (int i = 1; i <= size(A); i += 1) {
        // if (length(A->entries[i]) > 0) {
        moveFront(A->entries[i]);
        moveFront(B->entries[i]);
        while (index(A->entries[i]) != -1 && index(B->entries[i]) != -1) {
            Entry a = get(A->entries[i]);
            Entry b = get(B->entries[i]);
            // if column exists for a and b
            if (a->column == b->column) {
                changeEntry(S, i, a->column, a->value + b->value);
                if (eq) {
                    moveNext(A->entries[i]);
                } else {
                    moveNext(A->entries[i]);
                    moveNext(B->entries[i]);
                }
            }
            // if a exists but not b
            else if (a->column < b->column) {
                changeEntry(S, i, a->column, a->value);
                moveNext(A->entries[i]);
            }
            // if b exists but not a
            else if (a->column > b->column) {
                changeEntry(S, i, b->column, b->value);
                moveNext(B->entries[i]);
            }
        }
        while ((index(A->entries[i]) != -1)) {
            Entry a = get(A->entries[i]);
            changeEntry(S, i, a->column, a->value);
            moveNext(A->entries[i]);
        }
        while ((index(B->entries[i]) != -1)) {
            Entry b = get(B->entries[i]);
            changeEntry(S, i, b->column, b->value);
            moveNext(B->entries[i]);
        }
    }
    return S;
}

Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "A == NULL || B == NULL in diff()");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "size(A) != size(B)\n");
        exit(EXIT_FAILURE);
    }

    if (A == B) {
        Matrix E = newMatrix(size(A));
        return E;
    }
    Matrix C = scalarMult(-1, B);
    Matrix D = sum(A, C);
    freeMatrix(&C);
    return D;
}

Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "A == NULL || B == NULL");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "size(A) != size(B)");
        exit(EXIT_FAILURE);
    }
    Matrix P = newMatrix(size(A));
    Matrix BT = transpose(B);
    for (int i = 1; i <= size(A); i += 1) {
        if (length(A->entries[i]) > 0) {
            for (int j = 1; j <= size(BT); j += 1) {
                double dot_v = 0;
                moveFront(A->entries[i]);
                moveFront(BT->entries[j]);
                while (index(A->entries[i]) != -1 &&
                       index(BT->entries[j]) != -1) {
                    Entry a = get(A->entries[i]);
                    Entry b = get(BT->entries[j]);
                    if (a->column == b->column) {
                        dot_v += a->value * b->value;
                        moveNext(A->entries[i]);
                        moveNext(BT->entries[j]);
                    } else if (a->column < b->column) {
                        moveNext(A->entries[i]);
                    } else {
                        moveNext(BT->entries[j]);
                    }
                }
                if (dot_v != 0) {
                    changeEntry(P, i, j, dot_v);
                }
            }
        }
    }
    freeMatrix(&BT);
    return P;
}

void printMatrix(FILE *out, Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "M == NULL in printMatrix");
        exit(EXIT_FAILURE);
    }
    int i = 1;
    if (NNZ(M) != 0) {
        while (i <= size(M)) {
            if (length(M->entries[i]) != 0) {
                fprintf(out, "%d:", i);
                for (moveFront(M->entries[i]); index(M->entries[i]) != -1;
                     moveNext(M->entries[i])) {
                    Entry cur = (Entry)get(M->entries[i]);
                    fprintf(out, " (%d, %0.1f)", cur->column, cur->value);
                }
                fprintf(out, "\n");
            }
            i += 1;
        }
    }
}
