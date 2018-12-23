//Samer Baslan
//sbaslan
//CMPS101 Fall 2017
//11-31-2017
//pa5
//Graph.c -- ADT implemented as array of adjacency Lists 

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GREY 1
#define BLACK 2


typedef struct GraphObj{
	List* adjList;
	int* color;
	int* parent;
	int* discoveryt;
	int* finisht;
	int order; //|V|
	int size;  //|E|
}GraphObj;


/* Constructors-Destructors */

// newGraph()
// return a reference to a new graph object containing n vertices and no edges.
Graph newGraph(int n){
	Graph G;
	G = malloc(sizeof(struct GraphObj));
	G->adjList = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->discoveryt = calloc(n+1, sizeof(int));
	G->finisht = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	
	for(int i = 0; i < n+1; i++){
		G->adjList[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discoveryt[i] = UNDEF;
		G->finisht[i] = UNDEF;
	}
	
	return G;
}

// freeGraph()
// frees all heap memory associated with a graph and sets its Graph argument to NULL. 
void freeGraph(Graph* pG){
	Graph temp = *pG;
	
	for(int i = 1; i <= getOrder(temp); i++){
		freeList(&(temp->adjList[i]));
	}
	
		free(temp->color);
		free(temp->parent);	
		free(temp->discoveryt);
		free(temp->finisht);
		
		free(*pG);
		*pG = NULL;
	
}



/* Access functions */


// getOrder() 
// returns the number of vertices in G
int getOrder(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: getOrder() called on NULL Graph reference\n");
		exit(1);
	}
	return G->order;
}

// getSize()
// returns size of G
int getSize(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: getSize() called on NULL Graph reference\n");
		exit(1);
	}
	return G->size;
}

// getParent()
// returns parent of u
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: getParent() called on NULL Graph reference\n");
		exit(1);
	}
	if((u < 1) || (u > getOrder(G))){
		fprintf(stderr, "Graph Error: getParent() called on invalid vertex\n");
		exit(1);
	}
	else{
		return G->parent[u];
	}
}

// getDiscover()
// returns discovery time of u
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: getDiscover() called on NULL Graph reference\n");
		exit(1);
	}
	if((u < 1) || (u > getOrder(G))){
		fprintf(stderr, "Graph Error: getDiscover() called on invalid vertex\n");
		exit(1);
	}
	else{
		return G->discoveryt[u];
	}
}

// getFinish()
// returns finish time of u
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: getFinish() called on NULL reference\n");
		exit(1);
	}
	if((u < 1) || (u > getOrder(G))){
		fprintf(stderr, "Graph Error: getFinish() called on invalid vertex\n");
		exit(1);
	}
	else{
		return G->finisht[u];
	}
}




/* Manipulation procedures */



// addArc()
// Add directed edge to G from u to v
// Pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v){
	if((u < 1) || (u > getOrder(G)) || (v < 1) || (v > getOrder(G))){
		fprintf(stderr, "Graph Error: addArc() called on invalid vertices (u, v, or both) \n");
		exit(1);
	}
	if(length(G->adjList[u]) == 0){ //if empty adjList
		append(G->adjList[u], v);  //simply append v
	}
	else{
		moveFront(G->adjList[u]); //go through adjacency list
		while((index(G->adjList[u]) != -1) && (v > get(G->adjList[u]))){ //as long as it hasnt fallen off the end the elemnent in adjList
			moveNext(G->adjList[u]);									 // isnt bigger than v, go thru adjList
		}
		if(index(G->adjList[u]) < 0){ //if cursor undefined
			append(G->adjList[u], v); //just append
		}
		else{
			insertBefore(G->adjList[u], v); //otherwise insert v before current element
		}
	}
	G->size = G->size + 1;
}

// addEdge()
// Add undirected edge on G from u to v
// Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v){
	if((u < 1) || (u > getOrder(G)) || (v < 1) || (v > getOrder(G))){
		fprintf(stderr, "Graph Error: addEdge() called on invalid vertices (u, v, or both) \n");
		exit(1);
	}
	if(length(G->adjList[u]) == 0){
		append(G->adjList[u], v);
	}
	else{
		moveFront(G->adjList[u]);
		while((index(G->adjList[u]) != -1) && (v > get(G->adjList[u]))){ //go through adjacency list until appropriate position found
			moveNext(G->adjList[u]);
		}
		//append v if cursor falls off list
		if(index(G->adjList[u]) < 0){
			append(G->adjList[u], v); 
		}
		else{
			insertBefore(G->adjList[u], v); //insert v before current position of cursor
		}
	}
	
	//now same for u
	if(length(G->adjList[v]) == 0){
		append(G->adjList[v], u);
	}
	else{
		moveFront(G->adjList[v]);
		while((index(G->adjList[v]) != -1) && (u > get(G->adjList[v]))){
			moveNext(G->adjList[v]);
		}
		if(index(G->adjList[v]) < 0){
			append(G->adjList[v], u);
		}
		else{
			insertBefore(G->adjList[v], u);
		}
	}
	G->size = G->size + 1;
}

// visit()
// Recursive function within DFS where the real work gets done
void Visit(Graph G, List S, int u, int* time){
	
	G->color[u] = GREY;
	G->discoveryt[u] = ++*time;
	moveFront(G->adjList[u]);
	
	while(index(G->adjList[u]) >= 0){
		int v = get(G->adjList[u]);
		
		if(G->color[v] == WHITE){
			G->parent[v] = u;
			Visit(G, S, v, time);
		}
		moveNext(G->adjList[u]);
	}
	G->color[u] = BLACK;
	G->finisht[u] = ++*time;
	prepend(S, u);
}


// DFS()
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S){
	if(length(S) != getOrder(G)){ //pre
		fprintf(stderr, "Graph Error: DFS() called on different sizes\n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){ //initialize
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discoveryt[i] = UNDEF;
		G->finisht[i] = UNDEF;
	}
	int time = 0;
	moveFront(S);
	while(index(S) >= 0){
		int u = get(S);
		if(G->color[u] == WHITE){
			Visit(G, S, u, &time);
		}
		
		moveNext(S);
	}
	
	for(int i = length(S)/2; i > 0; i--){
		deleteBack(S);
	}

}




/* Other Functions */

// transpose()
Graph transpose(Graph G){
	Graph transposed = newGraph(getOrder(G)); //create transpose w/ order G
	
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->adjList[i]);
		
		while(index(G->adjList[i]) >= 0){
			addArc(transposed, get(G->adjList[i]), i);
			moveNext(G->adjList[i]);
		}
	}
	return transposed;
}

// copyGraph()
Graph copyGraph(Graph G){
	Graph copyg = newGraph(getOrder(G));
	
	for(int j = 0; j <= getOrder(G); j++){
		for(moveFront(G->adjList[j]); index(G->adjList[j]) > 0; moveNext(G->adjList[j])){
			addArc(copyg, j, get(G->adjList[j]));
		}
	}
	return copyg;
}

//printGraph()
void printGraph(FILE* out , Graph G){
	if(out == NULL || G == NULL){
		fprintf(stderr, "Graph Error: printGraph() called on NULL reference\n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adjList[i]);
		fprintf(out, "\n");
	}
}