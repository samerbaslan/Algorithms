import java.io.*;
import java.util.Scanner;
import java.util.Arrays;

class Lex{
   public static void main(String[] args) throws IOException{

      Scanner in = null;
      Scanner in1 = null;
      PrintWriter out = null;
      int n = 0;
      int count = 0;
   
      if(args.length != 2){
         System.err.println("Usage: Lex input output");
         System.exit(1);
      }
  
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      while(in.hasNextLine()){
         n++;
         in.nextLine();
      }
      in.close();
      in1 = new Scanner(new File(args[0]));
    
      String[] arr = new String[n]; //create new string array size n
      List alph = new List(); //alphabetical ordered list
      while(in1.hasNextLine()){
         arr[count] = in1.nextLine();
         count++;
      }
      alph.append(0); // append the first index of arr for comparison
      
      for(int i = 1; i < arr.length; i++){
         alph.moveFront();   // move cursor to the front of the list
         int j = 0;
         String s1 = arr[i]; // set comparison string
         while(j != i && s1.compareTo(arr[alph.get()]) >= 0){
            j++;
            alph.moveNext();
         }


         if(i == j){
            alph.append(i);
         }
         else{
            alph.insertBefore(i);
         }
      }
      
      alph.moveFront();       
      while(alph.index() >= 0){
         out.println(arr[alph.get()]);
         alph.moveNext();
      }
      
      in1.close();
      out.close();
   }
}
