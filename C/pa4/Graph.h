#include "List.h"
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define NIL -87 //W
#define INF -65 //A

// Exported reference type
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
// newGraph()
// Constructor: Returns reference to new Graph object
Graph newGraph(int n);

// freeGraph()
void freeGraph(Graph* pG);

/*** Access functions ***/
// getOrder()
// Returns the field storing the number of vertices
int getOrder(Graph G);

// getSize()
// Returns the field storing the number of edges
int getSize(Graph G);

// getSource()
// Returns the source vertex most recently used in BFS(), 
// or NIL if BFS() has not been called yet
int getSource(Graph G);

// getParent()
// Returns the parent of vertex u in the Breadth-First tree created by BFS()
// or NIL if BFS() has not yet been called
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u
// or INF if BFS() has not yet been called
int getDist(Graph G, int u);

// getPath()
// Appends to List L the vertices of a shortest path in G from source to u,
// or appends NIL if no such path exists
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

// makeNull()
// deletes all the edges of G, restoring to its original state
void makeNull(Graph G);

// addEdge()
// inserts a new edge joining u to v
void addEdge(Graph G, int u, int v);

// addArc()
// inserts a new directed edge from u to v
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif
