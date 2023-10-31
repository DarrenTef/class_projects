/*
 * Darren Lee, dlee181
 * 2023 Winter CSE101 PA2
 * FindPath.c
 * Executable Client program which takes the Graph ADT to find the shortest paths between pairs of vertices.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
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

    // Check if argc is greater than two
    if (infile == NULL) {
        fprintf(stderr, "Lex.c Error, could not open infile, NULL");
        exit(EXIT_FAILURE);
    }
    int num_vec, a, b;
    fscanf(infile, "%d", &num_vec);

    Graph G = newGraph(num_vec);
    while (fscanf(infile, "%d %d", &a, &b)) {
        if (a == 0 && b == 0) {
            break;
        }
        addEdge(G, a, b);
    }

    printGraph(outfile, G);

    while (fscanf(infile, "%d %d", &a, &b)) {
        if (a == 0 && b == 0) {
            break;
        }
        List P = newList();
        BFS(G, a);
        getPath(P, G, b);

        if (getDist(G, b) == INF) {
            fprintf(outfile, "The distance from %d to %d is infinity\nNo %d-%d path exists\n", a, b, a, b);
        }
        else {
            fprintf(outfile, "\nThe distance from %d to %d is %d\n", a, b, getDist(G, b));
            fprintf(outfile, "A shortest %d-%d path is:", a, b);
            printList(outfile, P);
            fprintf(outfile, "\n");
        }
        freeList(&P);
    }
    freeGraph(&G);
    fclose(infile);
    fclose(outfile);
    return 0;
}
