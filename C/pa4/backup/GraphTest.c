#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int n = 10;
   Graph G = newGraph(n); // create Graph of order 10
   
   printf("Order is %d\n", getOrder(G)); // prints out 6
   printf("Size is %d\n", getSize(G)); // prints out 0
   
   addEdge(G, 2, 6);
   addEdge(G, 3, 5);
   addEdge(G, 4, 10);
   addEdge(G, 1, 3);
   printGraph(stdout, G); 
   // 1: 3
   // 2: 6
   // 3: 1 5
   // 4: 10
   // 5: 3
   // 6: 2
   // 7: 0
   // 8: 0
   // 9: 0
   // 10: 4

   printf("Size is now %d\n", getSize(G)); // 4
   printf("Source is %d\n", getSource(G)); // NIL. BFS not called yet
   printf("Parent is %d\n", getParent(G, 3)); // NIL. BFS not called yet
   printf("Dist is %d\n", getDist(G,7));     // INF. BFS not called yet
   
   BFS(G, 5); // Source is 5
   List L = newList();
   getPath(L, G, 3);
   printf("The dist from 5 to 3 is: %d\n", getDist(G, 3)); // 1
   printf("The path from 5 to 3 is: "); // 5 3
   printList(stdout, L);
   printf("\n");

   freeList(&L);
   freeGraph(&G);
   return(0);
}
