/*
 * Darren Lee, dlee181
 * 2023 Winter CSE101 PA2
 * GraphTest.c
 * Testing the functions within Graph ADT
 */

// Testing for Graph.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "Graph.h"

int main(int argc, char* argv[]) {

    int n = 7;

    // Less than 1 returns an error
    Graph A = newGraph(n);
    Graph B = newGraph(n);
    Graph C = newGraph(1);

    // getOrder
    printf("7 %d\t 7 %d\t 1 %d\n", getOrder(A), getOrder(B), getOrder(C));

    // getSize
    printf("0 %d\t 0 %d\t 0%d\n", getSize(A), getSize(B), getSize(C));

    // getSource
    printf("NIL = -3\t-3 %d\t-3 %d\t-3 %d\n", getSource(A), getSource(B), getSource(C));

    // addEdge, BFS, getParent
    addEdge(A, 1, 2);
    addEdge(A, 1, 4);
    addEdge(A, 2, 3);
    addEdge(A, 3, 6);
    addEdge(A, 6, 5);
    addEdge(A, 4, 5);
    addEdge(A, 5, 7);

    // addArc
    addArc(B, 1, 2);
    addArc(B, 2, 3);
    addArc(B, 2, 5);
    addArc(B, 3, 4);
    addArc(B, 5, 4);
    addArc(B, 1, 5);
    addArc(B, 1, 6);
    addArc(B, 5, 7);
    printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
    printf("%d\n", getSize(B));
    assert(getSize(B) == 8);

    BFS(B, 1);
    printf("%d\n", getSource(B));
    //assert(getSource(A) == 1);
    printf("NIL%d\n", getParent(A, 1));
    printf("1%d\n", getParent(A, 2));
    printf("2%d\n", getParent(A, 3));
    printf("3%d\n", getParent(A, 4));
    printf("1%d\n", getParent(A, 5));
    printf("1%d\n", getParent(A, 6));
    printf("5%d\n", getParent(A, 7));
    printGraph(stdout, B);
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    printf("%d\n", getSize(A));
    //assert(getSize(A) == 7);
    BFS(A, 1);
    printf("%d\n", getSource(A));
    assert(getSource(A) == 1);
    printf("NIL%d\n", getParent(A, 1));
    printf("1%d\n", getParent(A, 2));
    printf("2%d\n", getParent(A, 3));
    printf("1%d\n", getParent(A, 4));
    printf("4%d\n", getParent(A, 5));
    printf("3%d\n", getParent(A, 6));
    printf("5%d\n", getParent(A, 7));
    // getDist
    printf("%d\n", getDist(A, 7));
    // printGraph
    printGraph(stdout, A);

    //freeGraph
    freeGraph(&A);
    freeGraph(&B);
    //freeGraph(&C);
    return (0);
}

