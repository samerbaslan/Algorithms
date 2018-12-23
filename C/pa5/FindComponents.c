//Samer Baslan
//sbaslan
//CMPS101 Fall 2017
//12-03-2017
//FindComponents.c -- top level client for Graph ADT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"List.h"
#include"Graph.h"

#define MAX_LEN 255

int main(int argc, char* argv[]){

   // check command line for correct number of arguments
   if(argc != 3){
      printf("Usage: %s <Infile> <Outfile>\n", argv[0]);
      exit(1);
   }
   
   // open files for reading and writing
   FILE *in, *out;
   
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   
   //error handling
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for reading\n", argv[2]);
      exit(1);
   }
   
   // store the vertex number into line
   char line[MAX_LEN];
   fgets(line, MAX_LEN, in);
   
   int vertices = 0;

   // scan line and store int in vertices
   sscanf(line, "%d", &vertices);
   Graph G = newGraph(vertices);

   List S = newList();
   // initialize stack
   for(int i = 1; i <= vertices; i++){
      append(S, i);
   }

   while(fgets(line, MAX_LEN, in) != NULL){
      int a = 0;
      int b = 0;
      // scan line and store the two values in a and b
      sscanf(line, "%d %d", &a, &b);
      if(a == 0 && b == 0){ // if the input is 0 0
         break; // break out of while loop
      }
      else{
         addArc(G, a, b); // add b to a's adjList
      }
   }
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out, "\n");

   // finding strongly connected components
   DFS(G, S);
   Graph tran = transpose(G);
   DFS(tran, S);
   
   int count = 0; //counter for scc
   
   moveFront(S);
   
   while(index(S) >= 0) {
      if(getParent(tran, get(S)) == NIL){
         count++;
	  }
      moveNext(S);
   }

   List temp = newList();
   fprintf(out, "G contains %d strongly connected components:\n", count);
   int i = 1;
   for(moveBack(S); index(S) != -1; movePrev(S)){
	   
      prepend(temp, get(S));
	  
      if(getParent(tran, get(S)) == NIL){   // traverse the list until source is found (parent == NIL)
         fprintf(out, "Component %d: ", i);
         printList(out, temp);
         fprintf(out, "\n");
         clear(temp);
         i++;
      }
   }
   
   freeGraph(&G);
   freeGraph(&tran);
   freeList(&S);
   freeList(&temp);
   fclose(in);
   fclose(out);
}