/*
 * Darren Lee, dlee181
 * 2023 Winter CSE101 PA2
 * Graph.h
 * Header file for Graph ADT
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

#define INF -2
#define NIL -3
#define WHITE -4
#define BLACK -5
#define GRAY -6
// Struct
typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
