#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs ---------------------------------------------------------------------
// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;
	
// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int curindex;
   int length;
} ListObj;

// Constructors-Destructors ----------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.

void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty Queue object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->curindex = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with Queue *pL, and sets *pL to NULL.S
void freeList(List* pL){
   if(pL != NULL && *pL != NULL){
//     Node N = (*pL)->front;
 //     while(N != NULL){
  //       Node temp = N;
  //       N = N->next;
  //       free(&temp);         // use temp because wont be able to point to N after it is freed
   //   }
      clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}
      
// Access functions------------------------------------------------------------
// length()
// Returns the number of elements in this List.
int length(List L){
   if(L==NULL){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return L->length;
}

// index()
// If cursor is defined, returns the index of the cursor element.
// other wisereturns -1.
int index(List L){
   if(L==NULL){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return L->curindex;
}

// front()
// Returns front element.
// Pre: length()>0
int front(List L){
   if(L==NULL){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   return L->front->data;
}

// back()
// Returns back element.
// Pre: length()>0 
int back(List L){
   if(L==NULL){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   return L->back->data;
}

// get()
// Returns cursor element.
// Pre: length()>0, index()>=0
int get(List L){
   if(L==NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->curindex < 0){
      printf("List Error: calling get() on undefined cursor");
   }
   return L->cursor->data;
}
   
// equals()
// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B){
   if(A == NULL || B == NULL){
      printf("List Error: calling equals() on empty List reference\n");      exit(1);
   } 
   if(A->length == B->length){
      Node tempfront = B->front;
      Node tempfront2 = A->front;
      while(tempfront->next != NULL && tempfront2->next != NULL){
         if(tempfront->data == tempfront2->data){
            tempfront = tempfront->next;
            tempfront2 = tempfront2->next;
         }
         else{
            return 0;
         }
      }
      return 1;
   }
   return 0;
}
      
// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this list to its original empty state.
void clear(List L){
   if(L == NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   Node N = L->front;
   while(N != NULL){
      Node temp = N;
      N = N->next;
      free(temp);
   }
 
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->curindex = -1;
}
// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
   if(L == NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0){
      L->cursor = L->front;
      L->curindex = 0;
   }
}
// moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
   if(L == NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0){
      L->cursor = L->back;
      L->curindex = L->length - 1;
   }
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step towards
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is defined does nothing.
void movePrev(List L){
   if(L == NULL){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->curindex != 0){
      L->cursor = L->cursor->prev;
      L->curindex = L->curindex - 1;
   }
   else if(L->cursor != NULL && L->curindex <= 0){
      L->cursor = NULL;
      L->curindex = -1;
   }
   else{ //do nothing
   }
}
   
      
// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor beomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
   if(L == NULL){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->curindex != L->length-1){
      L->cursor = L->cursor->next;
      L->curindex = L->curindex + 1;
   } 
   else if(L->cursor != NULL && L->curindex == L->length-1){
      L->cursor = NULL;
      L->curindex = -1;
   }
   else{ // do nothing
   }
} 

// prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
   if(L == NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
  
   Node N = newNode(data);
   if(L->length == 0){
      L->front = L->back = N;
   }
   else{
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
   }
   L->length = L->length + 1;
}

// append()
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
   if(L == NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data);
   if(L->length == 0){
      L->front = L->back = N;
   }
   else{
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length = L->length + 1;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
   if(L == NULL){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      printf("List Error: calling insertBefore() called on empty List");
      exit(1);
   }
   if(L->curindex < 0){
      printf("List Error: calling insertBefore() called on undefined cursor");
      exit(1);
   }
   Node N = newNode(data);
   if(L->cursor->prev == NULL){
      L->cursor->prev = N;
      N->next = L->cursor;
      L->front = N;
   }
   else{
      N->prev = L->cursor->prev;
      L->cursor->prev->next = N;
      N->next = L->cursor;
      L->cursor->prev = N;
   }
   L->length = L->length + 1;
   L->curindex = L->curindex + 1;
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
   if(L == NULL){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      printf("List Error: calling insertAfter() on empty list\n");
      exit(1);
   }
   if(L->curindex < 0){
      printf("List Error: calling insertAfter() on undefined cursor\n");
      exit(1);
   }
   Node N = newNode(data);
   if(L->cursor->next == NULL){
      L->cursor->next = N;
      N->prev = L->cursor;
      L->back = N;
   }
   else{
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next = N;
   }    
   L->length = L->length + 1;
   // dont need to increment cursor index because the element is inserted
   // after the cursor
}

// deleteFront()
// Deletes the front element.
// Pre: length()>0
void deleteFront(List L){
   if(L == NULL){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      printf("List Error: calling deleteFront() on empty List");
      exit(1);
   }
   Node temp = L->front;
   L->front = L->front->next;
   L->front->prev = NULL;
   L->length = L->length - 1;
   freeNode(&temp);
} 
      

// deleteBack()
// Deletes the back element.
// Pre: length()>0
void deleteBack(List L){
   if(L == NULL){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      printf("List Error: calling deleteBack() on empty List\n");
      exit(1);
   }
   Node temp = L->back;
   L->back = L->back->prev;
   L->back->next = NULL;
   L->length = L->length - 1;
   freeNode(&temp);
}
   

// delete()
// Deletes the cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   if(L == NULL){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      printf("List Error: calling delete() on empty List\n");
      exit(1);
   }
   if(L->curindex < 0){
      printf("List Error: calling delete() on undefined cursor\n");
      exit(1);
   }
   if(L->cursor == L->front){
      deleteFront(L);
   }
   else if(L->cursor == L->back){
      deleteBack(L);
   }
   else{ // cursor is in the middle
      Node temp = L->cursor;
      L->cursor->next->prev = L->cursor->prev;
      L->cursor->prev->next = L->cursor->next;
      L->length = L->length -1;
      L->cursor = NULL;
      L->curindex = -1;
      freeNode(&temp);
   }
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints a String representation of this List
void printList(FILE* out, List L){
   Node N = NULL;
   for(N = L->front; N!= NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the 
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
   List temp = newList();
   Node N = NULL;
   for(N = L->front; N!= NULL; N = N->next){
      append(temp, N->data);
   }
   return temp;
}
