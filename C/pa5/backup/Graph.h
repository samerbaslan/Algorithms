//Samer Baslan
//sbaslan
//CMPS101 Fall 2017
//11-31-2017
//PA5
//Graph.h -- Header file for Graph.c


#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define INF -2
#define NIL 0
#define UNDEF -1

#include "List.h"
#include <stdio.h>

typedef struct GraphObj* Graph; 

/* Constructors-Destructors */

Graph newGraph(int n);

void freeGraph(Graph* pG);

/* Access functions */

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u); // Pre: 1<=u<=n=getOrder(G)*/ 

int getDiscover(Graph G, int u); // Pre: 1<=u<=n=getOrder(G)*/ 

int getFinish(Graph G, int u); // Pre: 1<=u<=n=getOrder(G)*/ 

/* Manipulation procedures */

void makeNull(Graph G);

void addEdge(Graph G, int u, int v); // pre: 1<=u<=n, 1<=v<=n /*

void addArc(Graph G, int u, int v);  // pre: 1<=u<=n, 1<=v<=n /*

void DFS(Graph G, List S);

/* Other Functions */

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif
