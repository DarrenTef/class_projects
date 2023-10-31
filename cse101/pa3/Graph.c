/*
 * Darren Lee, dlee181
 * 2023 Spring CSE101 pa3
 * Graph.c
 * Graph ADT
 */

#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Structs --------------------------------------
typedef struct GraphObj {
    List *adj;
    int *colors;
    int *discover;
    int *finish;
    int *parent;
    int order;
    int size;
} GraphObj;

// Constructor - Destructors
// returns new Graph obj containing n vertices nad no edges
Graph newGraph(int n) {
    if (n <= 0) {
        fprintf(stderr, "Cannot have a graph with no vertices");
        exit(EXIT_FAILURE);
    }
    Graph g = malloc(sizeof(GraphObj));
    if (g == NULL) {
        fprintf(stderr, "Graph does not exist in newGraph, g == NULL");
        exit(EXIT_FAILURE);
    }
    // set the values and Allocate the memory
    g->order = n;
    g->size = 0;
    g->discover = calloc((n + 1), sizeof(int));
    g->finish = calloc((n + 1), sizeof(int));
    g->colors = calloc((n + 1), sizeof(int));
    g->parent = calloc((n + 1), sizeof(int));
    g->adj = calloc((n + 1), sizeof(List));

    if (g->discover == NULL || g->colors == NULL || g->parent == NULL ||
        g->adj == NULL || g->finish == NULL) {
        fprintf(stderr, "Failed to allocate memory in newGraph");
        exit(EXIT_FAILURE);
    }
    // set defaults for the arrays and Allocate them into the adj
    for (int i = 1; i < n + 1; i += 1) {
        g->adj[i] = newList();
        g->colors[i] = WHITE;
        g->parent[i] = NIL;
        g->discover[i] = UNDEF;
        g->finish[i] = UNDEF;
    }
    return g;
}

void freeGraph(Graph *pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= getOrder(*pG); i += 1) {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->discover);
        free((*pG)->finish);
        free((*pG)->colors);
        free((*pG)->parent);
        free((*pG)->adj);
        free(*pG);
        *pG = NULL;
    }
}

// Accessors ------------------------------------
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getOrder");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getSize");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getParent");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "u is out of range, in getParent");
        exit(EXIT_FAILURE);
    }
    if (G->parent[u] != NIL) {
        return G->parent[u];
    }
    return NIL;
}

int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getDiscover");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "u is out of range, in getDiscover");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getFinish");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "u is out of range, in getFinish");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// Manipulators ---------------------------------
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in addArc()");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "u is out of range in addArc");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        fprintf(stderr, "u is out of range in addArc");
        exit(EXIT_FAILURE);
    }
    if (length(G->adj[u]) == 0) {
        append(G->adj[u], v);
        G->size += 1;
        return;
    }

    for (moveFront(G->adj[u]); index(G->adj[u]) != -1; moveNext(G->adj[u])) {
        int j = get(G->adj[u]);
        if (v == j) {
            return;
        }
    }

    moveBack(G->adj[u]);
    while ((index(G->adj[u]) != -1)) {
        if (v > get(G->adj[u])) {
            insertAfter(G->adj[u], v);
            break;
        } else {
            movePrev(G->adj[u]);
        }
    }
    if (index(G->adj[u]) == -1) {
        prepend(G->adj[u], v);
    }
    G->size += 1;
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in addEdge");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "u is out of range in addEdge");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        fprintf(stderr, "u is out of range in addEdge");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
}

// What should we do if Length(S) != n
// What to is the 2nd condition asking for in the spec
// How do I implement the stack
void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in DFS");
        exit(EXIT_FAILURE);
    }
    if (S == NULL) {
        fprintf(stderr, "S == NULL, in DFS");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Length of S not equal to the size of Graph");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i += 1) {
        G->colors[i] = WHITE;
        G->parent[i] = NIL;
    }

    int time = 0;
    for (moveFront(S); index(S) != -1; moveNext(S)) {
        int x = get(S);
        if (G->colors[x] == WHITE) {
            visit(G, S, x, &time);
        }
    }

    for (int x = 1; x <= getOrder(G); x += 1) {
        deleteBack(S);
    }
}

// Helpers --------------------------------------
// implementation of passing time as a param
int visit(Graph G, List S, int x, int *time) {
    if (G == NULL) {
        fprintf(stderr, "G cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (S == NULL) {
        fprintf(stderr, "S cannot be NULL");
        exit(EXIT_FAILURE);
    }
    if (x <= 0 || x > getOrder(G)) {
        fprintf(stderr, "x needs to be greater than 0 or less than size of G");
        exit(EXIT_FAILURE);
    }
    G->discover[x] = ++(*time);
    G->colors[x] = GRAY;
    moveFront(G->adj[x]);
    for (int y = 1; y <= length(G->adj[x]); y += 1) {
        if (G->colors[get(G->adj[x])] == WHITE) {
            G->parent[get(G->adj[x])] = x;
            visit(G, S, get(G->adj[x]), time);
        }
        moveNext(G->adj[x]);
    }
    G->colors[x] = BLACK;
    prepend(S, x);
    G->finish[x] = ++(*time);
    return time;
}

Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in transpose");
        exit(EXIT_FAILURE);
    }
    Graph t = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i += 1) {
        moveFront(G->adj[i]);
        while (index(G->adj[i]) != -1) {
            addArc(t, get(G->adj[i]), i);
            moveNext(G->adj[i]);
        }
    }
    t->size = G->size;
    t->order = G->order;
    return t;
}

Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in copyGraph");
        exit(EXIT_FAILURE);
    }
    Graph copy = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i += 1) {
        moveFront(G->adj[i]);
        while (index(G->adj[i]) != -1) {
            addArc(copy, i, get(G->adj[i]));
            moveNext(G->adj[i]);
        }
    }
    copy->size = G->size;
    copy->order = G->order;
    return copy;
}

void printGraph(FILE *out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in printGraph");
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while (i <= getOrder(G)) {
        if (G->adj[i] != NULL) {
            fprintf(out, "%d:", i);
            printList(out, G->adj[i]);
        }
        i += 1;
    }
}
