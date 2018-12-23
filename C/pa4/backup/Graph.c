#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

#define white 1
#define gray 2
#define black 3
// structs --------------------------------------------------------------------
// private GraphObj type
typedef struct GraphObj{
   List *aList;
   int *aColor;
   int *aParent;
   int *aDist;
   int order;
   int size;
   int source;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Constructor: returns reference to new Graph object
Graph newGraph(int n){
   Graph G;
   G = malloc(sizeof(GraphObj));           // allocate space for Graph
   G->aList = calloc(n+1, sizeof(List));   // array for adjacency lists
   G->aColor = calloc(n+1, sizeof(int));   // array for colors
   G->aParent = calloc(n+1, sizeof(int));  // array for parents
   G->aDist = calloc(n+1, sizeof(int));    // array for distance
   G->order = n;
   G->size = 0;
   G->source = NIL;
   for(int i = 0; i < n+1; i++){           // initialize the arrays
      G->aList[i] = newList();
      G->aColor[i] = white;
      G->aParent[i] = NIL;
      G->aDist[i] = INF;
   }
   return(G);
}  
// freeGraph()
void freeGraph(Graph* pG){
   for(int i = 0; i < ((*pG)->order + 1); i++){ // free each adjacency list
      freeList(&((*pG)->aList[i]));
   }
      free((*pG)->aList);    // free the array aList
      free((*pG)->aColor);   // free the array of colors 
      free((*pG)->aParent);  // free the array of parents
      free((*pG)->aDist);    // free the array of distances
      free(*pG);            
      *pG = NULL;
}

/*** Access functions  ----------------------------------------------------- ***/
// getOrder()
// Returns the field storing the number of vertices
int getOrder(Graph G){
   return G->order;
}

// getSize()
// Returns the field storing the number of edges
int getSize(Graph G){
   return G->size;
}

// getSource()
// Returns the source vertex most recently used in BFS(), 
// or NIL if BFS() has not been called yet
int getSource(Graph G){
   return G->source;
}

// getParent()
// Returns the parent of vertex u in the Breadth-First tree created by BFS()
// or NIL if BFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
   if((u < 1) || (u > getOrder(G))){
      printf("Graph Error: calling getParent() on non-existing vertex\n");
      exit(1);
   }
   else{
      return G->aParent[u];
   }
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u
// or INF if BFS() has not yet been called
// pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
   if((u < 1) || (u > getOrder(G))){
      printf("Graph Error: calling getDist() on non-existing vertex\n");
      exit(1);
   }
   else{
      return G->aDist[u];
   }
}

// getPath()
// Appends to List L the vertices of a shortest path in G from source to u,
// or appends NIL if no such path exists
// pre: 1 <= u <= getOrder(G)
// pre: getSource(G) != NIL
void getPath(List L, Graph G, int u){
   if(getSource(G) == NIL){
      printf("Graph Error: calling getPath() before BFS() has been called\n");
      exit(1);
   }
   if((u < 1) || (u > getOrder(G))){
      printf("Graph Error: calling getPath() on non-existing vertex\n");
      exit(1);
   }
   else{
      int s = getSource(G);
      if(s == u){			     // base case
         append(L, s);			     // append the source
      }
      else if(getParent(G, u) == NIL){
         append(L, NIL);
      }
      else{
         getPath(L, G, getParent(G, u));     // recursively call getPath on the parent of u
         append(L, u);			     // append the vertex u
      }
   }
}

/*** Manipulation procedures  ----------------------------------------------- ***/

// makeNull()
// deletes all the edges of G, restoring to its original state
void makeNull(Graph G){
   for(int i = 0; i < G->order + 1; i++){
      clear(G->aList[i]);  		     // resets each list to its original empty state
   }
}     

// addEdge()
// inserts a new edge joining u to v
// pre: 1 <= u <= getOrder(G) and 1 <= v >= getOrder(G)
void addEdge(Graph G, int u, int v){
//  printf("%d %d\n", u, v);
   if((u < 1) || (u > getOrder(G)) || (v < 1) || (v > getOrder(G))){
      printf("Graph Error: calling addEdge() on a non-existing vertex (either u or v)\n");
      exit(1);
   }
   if(length(G->aList[u]) == 0){
      append(G->aList[u], v);
   }
   else{
      moveFront(G->aList[u]);
      while((index(G->aList[u]) != -1) && (v > get(G->aList[u]))){  // find the right part of the list
      //   printf("%d\n", index(G->aList[u]));
         moveNext(G->aList[u]);
      }
      if(index(G->aList[u]) == -1){
         append(G->aList[u], v); // if the cursor falls off the list, append v
      }
      else{
         insertBefore(G->aList[u], v); // otherwise, insert v before the cursor
      }
   }

   if(length(G->aList[v]) == 0){
      append(G->aList[v], u);
   }
   else{
      moveFront(G->aList[v]); // move the cursor to the front of the adjacent list of v
      while((index(G->aList[v]) != -1) && (u > get(G->aList[v]))){ // find the spot in the list
         moveNext(G->aList[v]);
      }
      if(index(G->aList[v]) == -1){
         append(G->aList[v], u); // if the cursor falls off the list, append u
      }
      else{
         insertBefore(G->aList[v], u); // otherwise, insert u before the cursor
      }
   }
   G->size++;
}
 
// addArc()
// inserts a new directed edge from u to v 
void addArc(Graph G, int u, int v){
   if((u < 1) || (u > getOrder(G)) || (v < 1) || (v > getOrder(G))){
      printf("Graph Error: calling addArc() on a non-existing vertex (either u or v)\n");
      exit(1);
   }
   if(length(G->aList[u]) == 0){
      append(G->aList[u], v);
   }
   else{
      moveFront(G->aList[u]);
      while((index(G->aList[u]) != -1) && (v > get(G->aList[u]))){ // find the spot in the list where v belongs
         moveNext(G->aList[u]);
      }
      if(index(G->aList[u]) == -1){ // if the cursor falls off the list, append v
         append(G->aList[u], v);
      }
      else{
         insertBefore(G->aList[u], v); // otherwise, insert v before the cursor
      }
   }
   G->size++;
}

// BFS()
// runs the BFS algorithm on Graph G with source s
void BFS(Graph G, int s){
   int x;
   for(x = 0; x < (getOrder(G) + 1); x++){
      G->aColor[x] = white;        // initialize all vertices as white (unchecked)
      G->aDist[x] = INF;           // initialize all distances as INF (no source yet)
      G->aParent[x] = NIL;         // initialize all parents as NIL (no source yet)
   }
   G->source = s;                  // set source as s
   G->aColor[s] = gray;            // set s color as gray
   G->aDist[s] = 0;                // set distance as 0 (because it is the source)
   G->aParent[s] = NIL;            // source has no parent
   List queue = newList();         // make the queue
   prepend(queue, s);              // add the source to the queue
   while(length(queue) > 0){
      x = front(queue);
      if(length(queue) == 1){      // if the length is just 1, cant deleteFront, so clear
         clear(queue);
      }
      else{
         deleteFront(queue);       // if not, just delete the front Node
      }
      for(moveFront(G->aList[x]); index(G->aList[x]) != -1; moveNext(G->aList[x])){
         int y = get(G->aList[x]);   // for all adjacent vertices
         if(G->aColor[y] == white){  // if unchecked
            G->aColor[y] = gray;     // check and change color to gray
            G->aDist[y] = G->aDist[x] + 1; // distance is x+1 to the source
            G->aParent[y] = x;             // parent is x
            append(queue, y);              // add to the queue
            
         }
         G->aColor[x] = black;       // set the color to black once done
      }           
   }
   freeList(&queue);
}

/*** Other operations ***/
// printGraph()
// prints the adjacency list representation of G to outfile
void printGraph(FILE* out, Graph G){
   if(G == NULL){
      printf("printGraph() called on a null Graph\n");
      exit(1);
   }
   for(int i = 1; i < (getOrder(G) + 1); i++){
      fprintf(out, "%d: ", i);
      printList(out, G->aList[i]);
      fprintf(out, "\n");
   }
}
