#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
#define MAX_LEN 255

int main(int argc, char* argv[]){
   FILE *in, *out;
   char line[MAX_LEN];
   int numVertices = 0;

   // check command line for correct number of arguments
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   
   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
      printf("Can not open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Can not open file %s for reading\n", argv[2]);
      exit(1);
   }
   
   // store the vertex number into line
   fgets(line, MAX_LEN, in);

   // scan line and store the int into numVertices
   sscanf(line, "%d", &numVertices);
   Graph G = newGraph(numVertices);
   while(fgets(line, MAX_LEN, in) != NULL){
      int x = 0;
      int y = 0;
      // scan line and store the two values in x and y respectively
      sscanf(line, "%d %d", &x, &y);
      if(x == 0 && y == 0){ // if the input is 0 0 (ends the first part of input)       
         break; // break out of the while loop
      }
      else{
         addEdge(G, x, y); // add x and y to eachother's adjacency lists
      }
   }
   printGraph(out, G);
   // move on to the second part of the input file
   while(fgets(line, MAX_LEN, in) != NULL){
      int i = 0; 
      int j = 0;
      sscanf(line, "%d %d", &i, &j); // scan second and store the two values in i&j
      if(i == 0 && j == 0){ // if the input is 0 0 (end of the second part)
         break; //break out of the while loop
      }
      BFS(G, i); // perform BFS from source i
      int dist = getDist(G, j); // find the distance from i to j
      fprintf(out, "\n");
      if(dist == INF){ // if distance is INFINITY
         fprintf(out, "The distance from %d to %d is %s\n", i, j, "infinity");
      }
      else{
         fprintf(out, "The distance from %d to %d is %d\n", i, j, dist);
      }
      List path = newList();
      getPath(path, G, j); // get the path of j to the source and write it in "path"
      if(front(path) == NIL){  // if the path is NIL
         fprintf(out, "No %d-%d path exists\n", i, j);
      } 
      else{
         fprintf(out, "A shortest %d-%d path is: ", i, j);
         printList(out, path);
         fprintf(out, "\n");
      }
      freeList(&path);
   }
   freeGraph(&G);
   fclose(in);
   fclose(out);
   return(0);
}
