/*
 * Darren Lee, dlee181
 * 2023 Winter CSE101 PA2
 * Graph.c
 * Graph ADT
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// BFS has a clear problem with the

// Structs -----------------------------------------------
typedef struct GraphObj {
    int* distance;
    int* colors;
    int* parent;
    List* adj;
    int order;              // The number of vertices
    int size;               // The number of edges
    int source;
} GraphObj;

// Helpers -----------------------------------------------

// Constructors - Destructors ----------------------------
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
    g->source = NIL;
    g->distance = calloc((n+1), sizeof(int));
    g->colors = calloc((n+1), sizeof(int));
    g->parent =  calloc((n+1), sizeof(int));
    g->adj = calloc((n+1), sizeof(List));

    if (g->distance == NULL || g-> colors == NULL || g->parent == NULL|| g->adj == NULL) {
        fprintf(stderr, "Failed to allocate memory in newGraph");
        exit(EXIT_FAILURE);
    }
    // set defaults for the arrays and Allocate them into the adj
    for (int i = 1; i < n + 1; i += 1) {
        g->adj[i] = newList();
        g->colors[i] = WHITE;
        g->parent[i] = NIL;
        g->distance[i] = INF;
    }
    return g;
}
// Check while Loop
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= getOrder(*pG); i += 1) {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->distance);
        free((*pG)->colors);
        free((*pG)->parent);
        free((*pG)->adj);
        free(*pG);
        *pG = NULL;
    }
}


// Getters -----------------------------------------------
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

int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getSource");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

// returns the parent of the verex u in the BFS tree created by BFS, or NIL;
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

// returns the distance from the most recent BFS source to vertex u, or inf if BFS not called
int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getDist");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "u is out of range, in getDist");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}

// Appends to the List L or G->adj the vertices of a shortest path in G from source u.
void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in getPath");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "cannot have a path without a source in getPath");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
         fprintf(stderr, "u is out of range, in getPath");
         exit(EXIT_FAILURE);
    }
    if (G->source == u) {
        append(L, G->source);
    }
    else if (G->parent[u] == NIL) {
        append(L, NIL);
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

// Setters -----------------------------------------------
// Deletes all edges of G, restoirng it to its original state

void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in makeNull");
        exit(EXIT_FAILURE);
    }
    // Clear the adj List
    for (int i = 1; i <= getOrder(G); i += 1) {
        if (G->adj[i]) {
            clear(G->adj[i]);
            G->colors[i] = WHITE;
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }
    }
    // G->order stays the same;
    G->size = 0;
    G->source = NIL;
}

// inserts a new edge and joins u to v. i.e adj[v] = u
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
    moveBack(G->adj[u]);
    while ((index(G->adj[u]) != -1)) {
        if (v > get(G->adj[u])) {
            insertAfter(G->adj[u], v);
            break;
        }
        else {
            movePrev(G->adj[u]);
        }
    }
    if (index(G->adj[u]) == -1) {
        prepend(G->adj[u], v);
    }
    G->size += 1;
}
// Does my Loop start at 2
void BFS (Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in BFS()");
        exit(EXIT_FAILURE);
    }
    if (s < 0 || s > G->order) {
        fprintf(stderr, "source is not in range in BFS()");
        exit(EXIT_FAILURE);
    }

    for (int x = 1; x <= getOrder(G); x += 1) {
        G->colors[x] = WHITE;
        G->distance[x] = INF;
        G->parent[x] = NIL;
    }
    G->source = s;
    G->colors[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;

    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        int x = front(Q);
        deleteFront(Q);
        moveFront(G->adj[x]);
        //for (int y = 0; y < length(G->adj[x]); y += 1) {
        while (index(G->adj[x]) >= 0) {
            int value = get(G->adj[x]);
            if (G->colors[value] == WHITE){
                G->colors[value] = GRAY;
                G->distance[value] = G->distance[x] + 1;
                G->parent[value] = x;
                append(Q, value);
            }
            moveNext(G->adj[x]);
        }
        G->colors[x] = BLACK;
    }
    freeList(&Q);
}

// Others ------------------------------------------------
void printGraph (FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "G == NULL, in printGraph");
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while (i <= getOrder(G)) {
        if (G->adj[i] != NULL) {
            fprintf(out, "%d: ", i);
            printList(out, G->adj[i]);
        }
        i += 1;
    }
}
