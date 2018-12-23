//Samer Baslan
//sbaslan
//CMPS 101
//10-17-2017
//Lex.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#define MAX_LEN 256

int main(int argc, char* argv[]){
   FILE *in, *out;
   char line[MAX_LEN];
   int n = 0; 
   int count = 0;

   // check command line for correct number of arguments
   if(argc != 3){
      printf("Usage: %s <input file> <outputfile>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   /* read each line of input file, then count the number of tokens */
   while(fgets(line, MAX_LEN, in) != NULL){
      count++;
   }
   // close file
   fclose(in);
   
   // open file to restart at the beginning
   in = fopen(argv[1], "r");
   
   // put lines of file into a String array
   char arr[count][MAX_LEN];
 
   while(fgets(line, MAX_LEN, in) != NULL){
      strcpy(arr[n], line);
      n++;
   }
   
   // new list ADT
   List alpha = newList();
   // append the first index of arr for comparison
   append(alpha, 0);
   for(int i = 1; i < count; i++){
      int x = i-1;
      
      char *temp = arr[i]; // set comparison string
      moveBack(alpha);     // move the cursor to the front of the list
      while(x >= 0 && strcmp(temp, arr[get(alpha)]) <= 0){
         x--;
         movePrev(alpha);
      	}
      // if the while loop has stopped that means either
      // the cursor has fallen off the list, or it has found
      // the word's correct place in the list
      if(index(alpha) < 0){            // if the cursor has fallen off the list
         prepend(alpha, i);
     }
      else{                 
         insertAfter(alpha, i);
      }
   }
   
   moveFront(alpha); // move cursor to the front in order to print
 
   for(int b = 0; b<count; b++){
      fprintf(out, "%s", arr[get(alpha)]);
      moveNext(alpha);
   }
   
   fclose(in);  // close in file
   fclose(out); // close out file
   
   // free list
   freeList(&alpha);
   
   return(0);

}

