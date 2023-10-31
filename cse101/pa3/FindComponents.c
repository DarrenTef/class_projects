/*
 * Darren Lee, dlee181
 * CSE101 pa3, Spring 2023
 * FindComponents.c
 * Executable Client file which utilizes ADTs
 */

#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *infile = stdin;
    FILE *outfile = stdout;

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

    int num_vec, a, b;
    fscanf(infile, "%d", &num_vec);

    Graph G = newGraph(num_vec);
    while (fscanf(infile, "%d %d", &a, &b)) {
        if (a == 0 && b == 0) {
            break;
        }
        addArc(G, a, b);
    }
    List S = newList();
    for (int i = 1; i <= num_vec; i += 1) {
        append(S, i);
    }

    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, G);
    DFS(G, S);
    Graph GT = transpose(G);
    DFS(GT, S);

    int count = 0;
    for (int a = 1; a <= getOrder(G); a += 1) {
        if (getParent(GT, a) == NIL) {
            count += 1;
        }
    }

    List* C = calloc(count, sizeof(List));

    for (int i = 0; i < count; i += 1) {
        C[i] = newList();
    }

    int c = count;
    fprintf(outfile, "\nG contains %d strongly connected components:\n", count);
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        int j = get(S);
        if (getParent(GT, j) == NIL) {
            c -= 1;
        }
        append(C[c], j);
    }

    for (int i = 1; i <= count; i += 1) {
        fprintf(outfile, "Component %d: ", i);
        printList(outfile, C[i - 1]);
        fprintf(outfile, "\n");
    }

    for (int i = 0; i < count; i += 1) {
        freeList(&C[i]);
    }


    freeList(&S);
    free(C);
    freeGraph(&GT);
    freeGraph(&G);
    fclose(infile);
    fclose(outfile);

    return (0);
}
