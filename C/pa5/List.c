//Samer Baslan
//sbaslan
//CMPS101 Fall 2017
//10-17-2017
//PA5
//List.c -- ADT implemented as a doubly linked list

#include<stdio.h>
#include<stdlib.h>

#include "List.h"


// private NodeObj type
typedef struct NodeObj{
   int data;
   
   //doubly linked
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
   int cursorindex;
   int length;
} ListObj;

// Constructors and Destructors ----------------------------------------------------

// newNode()
// Constructor: Returns reference to new Node object. Initializes next, prev, and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->cursorindex = -1;
   
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL){
   if(pL != NULL && *pL != NULL){
      while(!isEmpty(*pL)){
		  clear(*pL);
	  }
	  
	  free(*pL);
	  *pL = NULL;
   }
}
      
// Access functions------------------------------------------------------------
// length()
// Returns the number of elements in this List.
int length(List L){
   if(L==NULL){
		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
		exit(1);
   }
   return (L->length);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
// Used for freeing List
int isEmpty(List L){
	if(L==NULL){
		fprintf(stderr, "List Error: calling isEmpty() on a NULL List\n");
		exit(1);
	}
	return (L->length==0);
}


// index()
// If cursor is defined, returns index of cursor element. Otherwise, returns 0
int index(List L){
   if(L==NULL){
		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
		exit(1);
   }
   return (L->cursorindex);
}

// front()
// Returns front element.
// Pre: length()>0
int front(List L){
   if(L==NULL){
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
		exit(1);
   }
   
   if(L->length == 0){
		fprintf(stderr, "List Error: calling front() on empty List\n");
		exit(1);
   }
   
   return (L->front->data);
}

// back()
// Returns back element.
// Pre: length()>0 
int back(List L){
   if(L==NULL){
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
		exit(1);
   }
   if(L->length == 0){
		fprintf(stderr, "List Error: calling back() on empty list\n");
		exit(1);
   }
   
   return (L->back->data);
}

// get()
// Returns cursor element.
// Pre: length()>0, index()>=0
int get(List L){
   if(L==NULL){
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
		exit(1);
   }
   if(L->cursorindex == -1){
		fprintf(stderr, "List Error: calling get() on undefined cursor");
   }
   if(L->length == 0){
		fprintf(stderr, "List Error: calling get() on empty list\n");
   }
   
   return (L->cursor->data);
}
   
// equals()
// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B){
	int eq = 1;
	Node N = NULL;
	Node M = NULL;

	if( A==NULL || B==NULL ){
      fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
      exit(1);
	}

	N = A->front;
	M = B->front;
	if(A->length != B->length){
		return 0;
	}
	while( eq && N!=NULL){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
   return eq;
}
		
      
// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this list to its original empty state.
void clear(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   Node N = L->front;
   while(N != NULL){
	   Node temp = N;
	   N = N->next;
	   free(temp);
   }
   
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->cursorindex = -1;
   L->length = 0;
}
// moveFront()
// If List is non-empty, places the cursor under the front element.
void moveFront(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0){ //if List nonempty
      L->cursor = L->front;
      L->cursorindex = 0;
   }
}
// moveBack()
// If List is non-empty, places the cursor under the back element. Otherwise, do nothing.
void moveBack(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0){
      L->cursor = L->back;
      L->cursorindex = L->length - 1; //index would be -1 length of List at the back
   }
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step towards front.
// If cursor is defined and at front, cursor becomes undefined
void movePrev(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }  
   if(L->cursor != NULL && L->cursorindex != 0){
      L->cursor = L->cursor->prev;
      L->cursorindex = L->cursorindex - 1;
   }
   else if(L->cursor != NULL && L->cursorindex <= 0){
      L->cursor = NULL;
      L->cursorindex = -1;
   }
   else{ //do nothing
   }
}
   
      
// moveNext()
// Move cursor to next index. If undefined, do nothing. If defined and not at back, move to next.
// If cursor is defined and at back, cursor becomes undefined.
void moveNext(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->cursor != L->back) {
      L->cursor = L->cursor->next;
      L->cursorindex++;
   }
   else if(L->cursor != NULL && L->cursor == L->back) {
      L->cursor = NULL;
      L->cursorindex = -1;
   }
}

// prepend()
// Insert new element into this List. If List is nonempty, new element becomes front
void prepend(List L, int data){
   if(L == NULL){
      fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
  
   Node N = newNode(data); //new node to be added for new element
   if(L->length == 0){
	   L->front = L->back = N;
	   L->length++;
   }
   else{
	   L->front->prev = N;
	   N->next = L->front;
	   L->front = N;
	   
	   L->cursorindex++;
	   L->length++;
   }
}

// append()
// Insert new element into this List. If List is non-empty, new element becomes back
void append(List L, int data){
   if(L == NULL){
      fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data);
   if(L->length == 0){ //same as prepend
      L->front = L->back = N;
   }
   else{
      L->back->next = N;	//next address store new element
      N->prev = L->back;	//previous address store old back
      L->back = N;			//back of list is new element
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
   if(L == NULL){
      fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      fprintf(stderr, "List Error: calling insertBefore() called on empty List");
      exit(1);
   }
   if(L->cursorindex < 0){
      fprintf(stderr, "List Error: calling insertBefore() called on undefined cursor");
      exit(1);
   }
   Node N = newNode(data);
   if(L->cursor->prev == NULL){			//if cursor at the front
      L->front = N;						//new element becomes front
      L->cursor->prev = N;				//cursor of old front element now points to new front element
      N->next = L->cursor;				//new element next points to old front element
   }
   else{
      N->prev = L->cursor->prev;		 
      L->cursor->prev->next = N;		
      N->next = L->cursor;
   }
   L->length++;
   L->cursorindex++;
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
   if(L == NULL){
      fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      fprintf(stderr, "List Error: calling insertAfter() on empty list\n");
      exit(1);
   }
   if(L->cursorindex < 0){
      fprintf(stderr, "List Error: calling insertAfter() on undefined cursor\n");
      exit(1);
   }
   Node N = newNode(data);
   if(L->cursor->next == NULL){
      L->back = N;
      L->cursor->next = N;
      N->prev = L->cursor;
   }
   else{
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next = N;
   }    
   L->length++;
}

// deleteFront()
// Deletes the front element.
// Pre: length()>0
void deleteFront(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      fprintf(stderr, "List Error: calling deleteFront() on empty List");
      exit(1);
   }
   if(L->cursor == L->front){
	   L->cursor = NULL;
	   L->cursorindex = -1;
   }
   else{
	   L->cursorindex--;
   }
   
   Node temp = L->front;
   if(L->length > 1){ //if L has more than 1 element
	   L->front = L->front->next;
	   L->front->prev = NULL;
   }
   else{
	   L->front = NULL;
	   L->back = NULL;
   }
   
   L->length--;
   freeNode(&temp);
} 
      

// deleteBack()
// Deletes the back element.
// Pre: length()>0
void deleteBack(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      fprintf(stderr, "List Error: calling deleteBack() on empty List\n");
      exit(1);
   }
   if(L->cursor == L->back){
	   L->cursor = NULL;
	   L->cursorindex = -1;
   }
   
   Node temp = L->back;
   if(L->length > 1){
	   L->back = L->back->prev;
	   L->back->next = NULL;
   }
   else{
	   L->back = NULL;
	   L->front = NULL;
   }
   L->length--;
   freeNode(&temp);
}
   

// delete()
// Deletes the cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   if(L == NULL){
      fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(L->length <= 0){
      fprintf(stderr, "List Error: calling delete() on empty List\n");
      exit(1);
   }
   if(L->cursorindex < 0){
      fprintf(stderr, "List Error: calling delete() on undefined cursor\n");
      exit(1);
   }
   if(L->cursor == L->front){
      deleteFront(L);
   }
   else if(L->cursor == L->back){
      deleteBack(L);
   }
   else{ // special case cursor in middle
      Node N = L->cursor;
	  
	  Node Pr = L->cursor->prev;
	  Node Ne = L->cursor->next;
	  
	  Pr->next = Ne;
	  Ne->prev = Pr;
	  
	  L->cursor = N;
	  
	  L->length--;
	  freeNode(&N);  
   }
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints a String representation of this List
void printList(FILE* out, List L){
   Node N = NULL;
   
   if(L == NULL){
	   fprintf(stderr, "List Error: calling printList() on a NULL List reference\n");
	   exit(1);
   }
   
   for(N = L->front; N!= NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the 
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
	if(L == NULL){
		printf("List Error: copyList() called on NULL List reference\n");
		exit(1);
	}
   List temp = newList();
   Node N = NULL;
   for(N = L->front; N!= NULL; N = N->next){
      append(temp, N->data);
   }
   return temp;
}