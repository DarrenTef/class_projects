/*
 * Darren Lee, dlee181
 * 2023 Spring CSE101 PA2
 * GraphTest.c
 * Testing the functions within Graph ADT
 */

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = 8;
    List S = newList();
    Graph G = newGraph(n);
    Graph T = NULL, C = NULL;
    Graph A = newGraph(n);
    // getSize(A)
    printf("getSize() 0 %d\n", getSize(A));
    addArc(A, 8, 1);
    addArc(A, 8, 2);
    addArc(A, 8, 2);
    addArc(A, 8, 3);
    addArc(A, 1, 8);
    addArc(A, 1, 8);
    addArc(A, 1, 7);
    addArc(A, 1, 7);
    printf("%d\n", getSize(A));

    // getOrder
    printf("getOrder\n");
    printf("%d\n", getOrder(A));
    printf("%d\n", getOrder(G));


    for (int i = 1; i <= n; i++)
        append(S, i);

    addArc(G, 1, 2);
    addArc(G, 1, 5);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 2);
    addArc(G, 3, 4);
    addArc(G, 3, 6);
    addArc(G, 3, 7);
    addArc(G, 3, 8);
    addArc(G, 6, 5);
    addArc(G, 6, 7);
    addArc(G, 8, 4);
    addArc(G, 8, 7);
    printGraph(stdout, G);

    DFS(G, S);

    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for (int i = 1; i <= n; i++) {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i),
                getFinish(G, i), getParent(G, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");

    // getParent
    printf("getParent\n");
    printf("%d\n", getParent(G, 1));
    printf("%d\n", getParent(G, 2));
    printf("%d\n", getParent(G, 5));
    printf("%d\n", getParent(G, 6));

    // getDiscover
    printf("getDiscover\n");
    printf("%d\n", getDiscover(G, 1));
    printf("%d\n", getDiscover(G, 2));
    printf("%d\n", getDiscover(G, 3));
    printf("%d\n", getDiscover(G, 4));

    printf("getFinish\n");
    printf("%d\n", getFinish(G, 1));
    printf("%d\n", getFinish(G, 2));
    printf("%d\n", getFinish(G, 3));
    printf("%d\n", getFinish(G, 4));

    T = transpose(G);
    C = copyGraph(G);
    fprintf(stdout, "copyGraph\n");
    printGraph(stdout, C);
    fprintf(stdout, "transpose\n");
    printGraph(stdout, T);
    fprintf(stdout, "\n");

    DFS(T, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for (int i = 1; i <= n; i++) {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i),
                getFinish(T, i), getParent(T, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");


    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    freeGraph(&A);
    return (0);
}
